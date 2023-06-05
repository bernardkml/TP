#include "date.h" /* Cette inclusion n'est pas nécessaire */
#include "individu.h" /* Cette inclusion n'est pas nécessaire */
#include "laureat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 50 /* pour la fonction init_tab */

struct laureat_Turing ** init_tab (const char *, int *);
void select_tab_age (struct laureat_Turing **, int, int);
int reorganiser_tab_origine (struct laureat_Turing **, int, const char *);
void trier_tab_laureat_nom (struct laureat_Turing **, int);
void sauvegarder_tab_laureat (struct laureat_Turing **, int, const char *);


int main() {
  int taille = 0, nb_laureat_hors_USA;
  /* Déclaration et initialisation de tab */
	struct laureat_Turing **tab = init_tab ("laureats_Turing.txt", &taille);

  /* Affichage du tableau */
  printf("\nLes %d premiers lauréats du prix Turing :\n", taille);
  afficher_tab_laureat(tab, taille);
  /* Affichage des lauréats qui avaient moins de 45 ans révolus */
	/* le 15 mars de l'année de leur prix */
  printf("\nLes lauréats du tableau récompensés avant qu'ils aient 45 révolus :\n");
  select_tab_age(tab, taille, 45);
  /* Affichage du tableau réorganisé avec les lauréats nés hors des USA en tête de liste */
  nb_laureat_hors_USA = reorganiser_tab_origine(tab, taille, "États-Unis");
  printf("\nLe tableau réorganisé avec les %d lauréat(e)s né(e)s hors des USA :\n", nb_laureat_hors_USA);
  afficher_tab_laureat(tab, taille);
  /* Tri du tableau selon l'ordre lexicographique des noms de lauréats */
  trier_tab_laureat_nom(tab, taille);
  printf("\nLe tableau réordonné dans l'ordre lexicographique des noms des lauréats :\n");
  afficher_tab_laureat(tab, taille);

  /* Sauvegarde du dernier état du tableau dans le fichier laureats_Turing_sortie.txt */
  sauvegarder_tab_laureat(tab, taille, "laureats_Turing_sortie.txt");

  /* Nettoyage mémoire */
  detruire_tab_laureat(tab, taille);
  tab = NULL;
  printf("Mémoire libérée...\n");

  return EXIT_SUCCESS;
}

/** Fonction qui alloue de l'espace sur le tas pour une chaîne de n caractères */
/** et renvoie l'adresse du bloc, de taille n+1, alloué */
char * allouer_chaine (int n) {
  char *str = malloc((n+1)*sizeof(char));
	if (str == NULL) {
		perror("Échec allocation chaine de caractères (struct individu ou ville)");
		exit(EXIT_FAILURE);
	}
  return str;
}

/** Fonction qui réorganise le tableau d'adresses de lauréats tab, de taille n, */
/* en plaçant en tête ceux qui ont été créés dans la ville v */
/* Cette fonction renvoie le nombre de laureats du tableau créés dans la ville v */
/** Complexité : \Theta(n) si n est la taille du tableau */
int reorganiser_tab_origine (struct laureat_Turing * tab[], int taille, const char * pays) {
	int i = -1, j = taille;
	for (;;)
	{
		while (strcmp(pays, tab[++i]->laureat->origine)) { if (i == taille-1) { break; } }
		while (!strcmp(pays, tab[--j]->laureat->origine)) { if (j == 0) { break; } }
		if (i >= j) { break; }
		echanger_laureat (tab + i, tab + j);
	}
	return i;
}

/** Fonction qui affiche tous les lauréats du tableau tab, de taille taille, */
/* récompensés avant qu'ils aient a révolues */
/** Complexité : \Theta(N) si N est la taille du tableau */
void select_tab_age (struct laureat_Turing *tab[], int taille, int a) {
	int i, a_revolu, trouve = 0;
	struct date * d = allouer_date();
  d->jour = 15;
  d->mois = 3;
	for (i = 0; i < taille; ++i) {
		d->annee = tab[i]->annee_prix;
		if ( (a_revolu = nbre_annees_revolues(tab[i]->laureat, d)) < a ) {
			trouve = 1;
			afficher_laureat(tab[i]);
			printf("[%s avait %d ans]\n", tab[i]->laureat->nom, a_revolu);
		}
	}
	if (!trouve)
		printf("Aucun lauréat récompensé avant qu'il ait %d ans révolus\n", a);
}

/** Fonction qui alloue de l'espace sur la tas pour un tableau de lauréats, */
/* l'initialise avec les informations stockées dans le fichier de nom n_fich */
/* et renvoie l'adresse du tableau ainsi initialisé */
/** N.B. l'entier pointé par le 2e paramètre d'entrée */
/* prend la valeur du nombre de lauréats référencés dans le tableau initialisé */
struct laureat_Turing ** init_tab (const char *n_fich, int * taille) {
	int i;
  FILE * f;
  struct laureat_Turing ** tab_res;
  struct date *tmp_date = allouer_date();
	char *tmp_prenom, *tmp_nom, *tmp_origine;
  /** Ouverture du fichier de nom n_fich en lecture */
	if ((f=fopen(n_fich,"r")) == NULL) {
		fprintf(stderr, "fichier %s introuvable \n", n_fich);
		exit(EXIT_FAILURE);
	}
	/* Lecture du nombre de lauréats dans le fichier (1re ligne du fichier) */
  fscanf(f,"%d\n", taille);
  /* Allocation d'espace sur le tas pour un tableau de lauréats de taille adéquate */
  /* et pour les struct laureat_Turing référencées dans le tableau */
  tab_res = allouer_tab_laureat(*taille);
	/* N.B. On suppose que les noms, prénoms et pays d'origine */
  /* des lauréats Turing du fichier laureats_Turing.txt */
  /* ont au plus TAILLE_MAX caractères */
	tmp_prenom = allouer_chaine(TAILLE_MAX);
	tmp_nom = allouer_chaine(TAILLE_MAX);
	tmp_origine = allouer_chaine(TAILLE_MAX);
	/* Récupération des lauréats stockés dans le fichier */
	for (i = 0; i < *taille; ++i) {
		/* Lecture des nom et prénom du lauréat et de l'année du prix */
		if (fscanf(f,"%s %s [%u] ", tmp_prenom, tmp_nom, &tab_res[i]->annee_prix) != 3) {
			perror("Échec lecture fichier");
			exit(EXIT_FAILURE);
		}
		/* Lecture de la date et du pays de naissance */
    if (fscanf(f,"né le %u/%u/%u %s\n", &tmp_date->jour, &tmp_date->mois, &tmp_date->annee, tmp_origine) != 4) {
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

/** Fonction qui trie le tableau de lauréats Turing tab, de taille n, */
/* selon l'ordre lexicographique des noms de compositeur (tri par insertion) */
/** Complexité : \Theta(n^2) */
void trier_tab_laureat_nom (struct laureat_Turing *tab[], int n) {
	int i,j;
  for(i = 1; i < n; ++i) {
    j = i;
    while( j >= 1 && ( strcmp(tab[j]->laureat->nom, tab[j-1]->laureat->nom) < 0
    || (!strcmp(tab[j]->laureat->nom, tab[j-1]->laureat->nom) && strcmp(tab[j]->laureat->prenom, tab[j-1]->laureat->prenom) < 0 ) ) ) {
      echanger_laureat(tab + j, tab + j - 1);
      j --;
    }
  }
}


/** Fonction qui sauvegarde le tableau de laureats tab, de taille n, */
/*  dans le fichier de nom n_fich */
void sauvegarder_tab_laureat (struct laureat_Turing **tab, int n, const char *n_fich) {
  int i;
  FILE *f;
  /** Ouverture du fichier de nom n_fich en écriture */
	if ((f=fopen(n_fich,"w")) == NULL) {
		fprintf(stderr, "ouverture fichier %s impossible \n", n_fich);
		exit(EXIT_FAILURE);
	}
  fprintf(f, "%d\n", n);
  for (i = 0; i < n; ++i) {
    fprintf(f, "%s %s [%u] ", tab[i]->laureat->prenom, tab[i]->laureat->nom, tab[i]->annee_prix);
    fprintf(f, "né le %u/%u/%u ", tab[i]->laureat->naissance->jour, tab[i]->laureat->naissance->mois, tab[i]->laureat->naissance->annee);
    fprintf(f, "%s\n", tab[i]->laureat->origine);
  }
  fclose(f);
}
