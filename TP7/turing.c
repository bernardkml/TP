#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <string.h>
#include "date.h"
#include "individu.h"
#include "turing.h"


/* declaration constantes et types utilisateurs */
#define TAILLE_MAX 23
/* declaration de fonctions utilisateurs */
struct laureat_Turing ** init_tab (char *n_fich, int * taille);
void afficher_laureat(struct laureat_Turing ** lt);
void select_tab_age (struct laureat_Turing *tab[], int taille, int a);
int reorganiser_tab_origine (struct laureat_Turing * tab[], int taille, const char * pays);
char * allouer_chaine (int n);
void detruire_laureat (struct laureat_Turing ** lt);
struct laureat_Turing * allouer_laureat (void);
struct laureat_Turing ** allouer_tab_laureat (int n);
void echanger_laureat (struct laureat_Turing **lt1, struct laureat_Turing **lt2);
int nbre_annees_revolues (const struct individu * ind, const struct date * d);
int age_revolu (const struct individu * ind, const struct date * d);
/* fonction principale */
int main()
{
    /* declaration et initialisation des variables */
    int taille = 0, i, j, k, l;
    struct laureat_Turing **tab = init_tab("laureats_Turing.txt", &taille);
    /* ici faire quelque chose */
	printf("Lauréats au Prix Turing : \n\n");
    for (i = 0; i < TAILLE_MAX; ++i)
    {
        afficher_laureat(tab+i);
    }
	printf("\n");
	printf("Lauréats au Prix Turing qui n'avait pas encore 45 ans révolus le 15 mars : \n\n");
	for (k = 0; k < TAILLE_MAX; ++k)
	{
		select_tab_age(tab, TAILLE_MAX, 45);
	}
	printf("\n");
	printf("Tableau de Lauréats réorganisé : \n\n");
	reorganiser_tab_origine(tab, TAILLE_MAX, "États-Unis");
	for ( l = 0; l < TAILLE_MAX; ++l)
	{
		afficher_laureat(tab+l);
	}

    for (j = 0; j < TAILLE_MAX; ++j)
    {
        detruire_laureat(tab+j);
    }
    free(tab);
    tab = NULL;
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
/** Fonction qui initialise un tableau de lauréats Turing */
/* avec les lauréats stockés dans le fichier de nom n_fich */
/* et renvoie l'adresse du tableau ainsi initialisé */
/** N.B. L'entier pointé par le 2e paramètre d'entrée */
/* prend la valeur du nombre de lauréats référencés dans le tableau initialisé */
struct laureat_Turing ** init_tab (char *n_fich, int * taille) {
	int i;
  FILE * f;
  struct laureat_Turing ** tab_res;
  struct date *tmp_date = allouer_init_date(0,0,0);
	char *tmp_prenom, *tmp_nom, *tmp_origine;
  /** Ouverture du fichier de nom n_fich en lecture */
	if ((f=fopen(n_fich,"r")) == NULL) {
		fprintf(stderr, "fichier %s introuvable \n", n_fich);
		exit(EXIT_FAILURE);
	}
	fscanf(f,"%d\n", taille);
  /* et stockage de son contenu dans le tableau tab_res */
  tab_res = allouer_tab_laureat(*taille);
	/* N.B. On suppose que les noms, prénoms et pays d'origine */
  /* des lauréats Turing du fichier laureats_Turing.txt */
  /* ont au plus TAILLE_MAX caractères */
	tmp_prenom = allouer_chaine(TAILLE_MAX);
	tmp_nom = allouer_chaine(TAILLE_MAX);
	tmp_origine = allouer_chaine(TAILLE_MAX);
	/* Récupération des lauréats stockés dans le fichier */
	for (i = 0; i < *taille; i++) {
		/* Lecture des nom et prénom du lauréat et de l'année du prix */
		if (fscanf(f,"%s %s [%u] ", tmp_prenom, tmp_nom, &tab_res[i]->annee_prix) != 3) {
			perror("Échec lecture fichier");
			exit(EXIT_FAILURE);
		}
		/* Lecture de la date et du pays de naissance */
    if (fscanf(f,"né le %u/%u/%u %s \n", &tmp_date->jour, &tmp_date->mois, &tmp_date->annee, tmp_origine) != 4) {
			perror("Échec lecture fichier");
			exit(EXIT_FAILURE);
		}
		tab_res[i]->laureat = allouer_init_individu(tmp_prenom, tmp_nom, tmp_date, tmp_origine);
	}
	/* Nettoyage : libération de la mémoire auxiliaire allouée sur la tas */
  detruire_date(&tmp_date);
  free(tmp_prenom);
  free(tmp_nom);
  free(tmp_origine);
  /* Fermeture du fichier */
  fclose(f);
  return tab_res;
}

/** Fonction qui affiche le titre, le prénom et le nom du laureat, (la date et la ville de création) de l'ltéra lt */
void afficher_laureat (struct laureat_Turing ** lt) {
	afficher_individu((*lt)->laureat);
	printf(" [lauréat %u]",(*lt)->annee_prix);
	printf("\n");
}

/** Fonction qui affiche tous les lauréats du tableau tab, de taille taille, */
/* récompensés avant qu'ils aient a révolues */
/** Complexité : \Theta(N) si N est la taille du tableau */
void select_tab_age (struct laureat_Turing *tab[], int taille, int a) {
	int i, a_revolu, trouve = 0;
	struct date * d = allouer_init_date(15, 3, 0);
	for (i = 0; i < taille; ++i) {
		d->annee = tab[i]->annee_prix;
		if ( (a_revolu = age_revolu(tab[i]->laureat, d)) < a ) {
			trouve = 1;
			afficher_laureat(&tab[i]);
			printf("[%s avait %d ans]\n", tab[i]->laureat->nom, a_revolu);
		}
	}
	if (!trouve)
		printf("Aucun lauréat récompensé avant qu'il ait %d ans révolus\n", a);
}

/** Fonction qui réorganise le tableau d'adresses de lauréats tab, de taille n, */
/* en plaçant en tête ceux qui ont été créés dans la ville v */
/* Cette fonction renvoie le nombre de laureats du tableau créés dans la ville v */
/** Complexité : \Theta(n) si n est la taille du tableau */
int reorganiser_tab_origine (struct laureat_Turing * tab[], int taille, const char * pays) 
{

	int d = taille - 1, g = 0;
	while (g < d)
	{
		while (strcmp(pays, tab[g]->laureat->origine) && (g < taille ))
		{
			g++;
		} 
		while (!strcmp(pays, tab[d]->laureat->origine) && (d >= 0))
		{
			d--;
		}
		echanger_laureat(tab + g, tab + d);
	}
	return g;
}

/** Fonction qui libère tout l'espace mémoire occupé sur le tas */
/* par le lauréat Turing pointé par lt */
void detruire_laureat (struct laureat_Turing ** lt) {
	detruire_individu(&(*lt)->laureat);
	free(*lt);
  *lt = NULL;
}

/** Fonction qui alloue de l'espace sur le tas pour une chaîne de n caractères */
/** et renvoie l'adresse du bloc, de taille n+1, alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
char * allouer_chaine (int n) {
  char *str = malloc((n+1)*sizeof(char));
	if (str == NULL) {
		perror("Échec allocation chaine de caractères (struct individu ou ville)");
		exit(EXIT_FAILURE);
	}
  return str;
}

/** Fonction qui alloue de l'espace sur le tas pour un lauréat */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR allouer_tab_laureat */
struct laureat_Turing * allouer_laureat (void) {
		struct laureat_Turing * lt = malloc(sizeof(struct laureat_Turing));
		if (lt == NULL) {
			perror("Échec allocation lauréat");
			exit(EXIT_FAILURE);
		}
		return lt;
}

/** Fonction qui alloue l'espace mémoire sur le tas */
/* pour un tableau de n adresses de lauréats */
/* (et pour n structures laureat_Turing) */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
struct laureat_Turing ** allouer_tab_laureat (int n) {
	int i;
	struct laureat_Turing ** t = malloc (sizeof(struct laureat_Turing *) * n);
	if (t == NULL) {
		perror("Échec allocation tableau");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; ++i)
		t[i] = allouer_laureat();
	return t;
}

/** Fonction qui échange les adresses de lauréats pointées par les deux arguments */
void echanger_laureat (struct laureat_Turing **lt1, struct laureat_Turing **lt2) {
	struct laureat_Turing *tmp = *lt1;
	*lt1 = *lt2;
	*lt2 = tmp;
}


/** Fonction qui calcule le nombre d'annÃ©es rÃ©volues de l'individu ind Ã  la date d */
/** Par exemple, un individu nÃ© le 7 avril 1950 a 49 annÃ©es rÃ©volues le 7 avril 2000 et en a 50 le 8 avril 2000 */
/** ComplexitÃ© : \Theta(1) */
int age_revolu (const struct individu * ind, const struct date * d) {
	struct date naissance_copie = *(ind->naissance);
	unsigned res = d->annee - (naissance_copie.annee + 1);
	naissance_copie.annee += res + 1;
	if (comparer_date(&naissance_copie, d) < 0)
		res ++;
	return res;
}

