#include "opera.h"
#include "individu.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 50 /* pour la fonction initialiser_tab_operas_fichier */

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

/** Fonction qui alloue de l'espace sur le tas pour un opéra */
/* et renvoie l'adresse du bloc alloué */
struct opera * allouer_opera (void) {
		struct opera * op = malloc(sizeof(struct opera));
		if (op == NULL) {
			perror("Échec allocation opéra");
			exit(EXIT_FAILURE);
		}
		return op;
}

/** Fonction qui libère toute la mémoire occupée par l'opéra pointé par op */
void detruire_opera (struct opera ** op) {
	free((*op)->titre);
	free((*op)->ville_creation);
	detruire_date(&(*op)->date_creation);
	detruire_individu(&(*op)->compositeur);
	free(*op);
  *op = NULL;
}

/** Fonction qui libère tout l'espace mémoire occupé sur le tas par le tableau d'opéras tab, de taille taille, */
void detruire_tab_opera (struct opera **tab[], int taille) {
	int i;
	for (i = 0; i < taille; ++i) {
		detruire_opera ((*tab) + i);
	}
	free(*tab);
  *tab = NULL;
}

/** Fonction qui affiche le titre, le prénom et le nom du compositeur, (la date et la ville de création) de l'opéra op */
void afficher_opera (const struct opera * op) {
	printf("%s créé le ", op->titre);
  afficher_date(op->date_creation);
  printf(" à %s, ", op->ville_creation);
  afficher_individu(op->compositeur);
}

/** Fonction qui réorganise le tableau de pointeurs d'opéra tab, de taille n, */
/* en plaçant en tête ceux qui ont été créés dans la ville v */
/* Cette fonction renvoie le nombre d'opéras du tableau créés dans la ville v */
/** Complexité : \Theta(n) si N est la taille du tableau */
/* int reorganiser_tab_opera_ville (struct opera * tab[], int taille, const char * v) {
	int i = -1, j = taille;
	for (;;)
	{
		while (!strcmp(v, tab[++i]->ville_creation)) if (i == taille-1) break;
		while (strcmp(v, tab[--j]->ville_creation)) if (j == 0) break;
		if (i >= j) break;
		echanger_opera (&tab[i], &tab[j]);
	}
	return i;
}
*/

/** Variante */
/** Complexité : \Theta(N) si N est la taille du tableau */
/*
int reorganiser_tab_opera_ville (struct opera * tab[], int taille, const char * v) {
	int i; j;
	for (j = 0; j < taille && !strcmp(v, tab[j]->ville_creation); j ++);
	for (i = j + 1; i < n; i ++) {
		if (!strcmp(v, tab[i]->ville_creation)) {
			echanger_opera (&tab[i], &tab[j]);
			j ++;
		}
	}
	return j;
}
*/

/** Fonction qui affiche les opéras, référencés dans le tableau t, de taille n, */
/* qui ont été créés dans la ville de naissance de leur compositeur */
void select_tab_ville_creation (struct opera **t, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if (!strcmp(t[i]->ville_creation, t[i]->compositeur->origine)) {
			afficher_opera(t[i]);
			printf("\n");
		}
	}
}


/** Fonction qui supprime du tableau t */
/*  tous les opéras dont le compositeur avait a années révolues lors de la création */
/* et renvoie l'adresse du nouveau tableau */
/* N.B. La taille du tableau est mise à jour */
/** Complexité : \Theta(N) si N est la taille du tableau */
struct opera ** supprimer_tab_age_compositeur (struct opera **t, int *n, int a) {
	int i, j = 0, taille = *n, nb_supp = 0; /* nb_supp = nombre de références supprimées */
	struct opera **nouv_t;
	for (i = 0; i < taille; ++i) {
		if (nbre_annees_revolues(t[i]->compositeur, t[i]->date_creation) >= a) {
			detruire_opera(&t[i]);
      t[i] = NULL;
			++nb_supp;
		}
	}
	*n = taille - nb_supp;
	nouv_t = malloc((*n)*sizeof(struct opera *));
  if (nouv_t == NULL) {
    perror("Erreur réallocation tableau d'opéras");
    exit(EXIT_FAILURE);
  }
	for (i = 0; i < taille; ++i) {
		if (t[i] != NULL) {
			nouv_t[j] = t[i];
			++j;
		}
	}
	free(t);
	return nouv_t;
}

/** Fonction qui recherche dans le tableau d'opéras tab, de taille taille, */
/* SUPPOSÉ TRIÉ DANS L'ORDRE CHRONOLOGIQUE DE CRÉATION, un opéra créé au cours de l'année an */
/** Cette fonction affiche un tel opéra s'il s'en trouve un dans le tableau */
/* et affiche un message d'absence sinon */
/** Complexité : \Theta(\log_2 N) si N est la taille du tableau */
void recherche_tab_annee_creation (struct opera *tab[], int taille, unsigned an) {
	if (taille > 0) {
		int milieu = taille/2;
		if (an > tab[milieu]->date_creation->annee)
			recherche_tab_annee_creation (tab+milieu+1, taille-milieu-1, an);
		else
			if (an < tab[milieu]->date_creation->annee)
				recherche_tab_annee_creation (tab, milieu, an);
			else
				afficher_opera(tab[milieu]);
	}
	else
		printf("Aucun opéra créé en %d dans le tableau \n", an);
}


/** Variante de la fonction recherche_tab_annee_creation */
/** Complexité : \Theta(\log_2 N) si N est la taille du tableau */
/*
void recherche_tab_annee_creation (unsigned int an, struct opera *tab[], int n) {
	int milieu = n/2;
	if (n <= 0) {
		printf("Aucun opéra créé en %u dans le tableau \n", an);
		return;
	}
	if (an > tab[milieu]->date_creation.annee) {
		recherche_tab_annee_creation (an, tab+milieu+1, n-milieu-1);
		return;
	}
	if (an < tab[milieu]->date_creation.annee) {
		recherche_tab_annee_creation (an, tab, milieu);
		return;
	}
	afficher_opera(tab[milieu]);
	return;
}
*/

/** Fonction qui renvoie la position de l'opéra le plus anciennement créé dans le tableau d'opéras tab */
/** Complexité : \Theta(N) si N est la taille du tableau */
/*
int recherche_pos_opera_ancien (struct opera *tab[], int taille) {
	int i;
  int pos_opera_ancien = 0;
  for(i = 1; i < taille; ++i) {
    if ( comparer_date(tab[i]->date_creation,tab[pos_opera_ancien]->date_creation) < 0)
      pos_opera_ancien = i;
  }
  return pos_opera_ancien;
}
*/

/** Fonction qui échange les adresses d'opéra pointées par les deux arguments */
void echanger_opera (struct opera **op1, struct opera **op2) {
	struct opera *temp = *op1;
	*op1 = *op2;
	*op2 = temp;
}

/** Fonction qui trie le tableau d'opéras tab, de taille n, */
/* selon l'ordre chronologique de création (tri à bulles avec A-R) */
/** Complexité : \Theta(N^2) si N est la taille du tableau */
void trier_tab_date_creation (struct opera **tab, int n) {
	int j, deb = 0, fin = n-1, der;
	while (deb < fin) {
		der = 0;
		for (j = deb; j < fin; ++j) {
      if (comparer_date(tab[j]->date_creation, tab[j+1]->date_creation) > 0) {
        echanger_opera(tab+j, tab+j+1);
        der = j;
      }
    }
    fin = der;
		for (j = fin; j > deb; --j) {
      if (comparer_date(tab[j-1]->date_creation, tab[j]->date_creation) > 0) {
        echanger_opera(tab+j, tab+j-1);
        der = j;
      }
    }
    deb = der;
	}
}

/** Fonction qui trie le tableau d'opéras tab, de taille n, */
/* selon l'ordre lexicographique des noms de compositeur (tri par insertion) */
/** Complexité : \Theta(N^2) si N est la taille du tableau */
/*
void trier_tab_opera_compositeur (struct opera *tab[], int taille) {
	int i,j;
  for(i = 1; i < taille; ++i){
    j = i;
    while( j >= 1 && (strcmp(tab[j]->compositeur->nom,tab[j-1]->compositeur->nom)) < 0 ) {
      echanger_opera(&tab[j], &tab[j-1]);
      j --;
    }
  }
}
*/

/** Fonction qui crée et renvoie l'adresse d'un tableau d'opéras de taille taille */
struct opera ** allouer_tab_opera (int taille) {
	int i;
	struct opera ** res = malloc (sizeof(struct opera *) * taille);
	for (i = 0; i < taille; i ++)
		res[i] = allouer_opera();
	return res;
}

/** Fonction qui affiche tous les opéras du tableau d'opéras tab, de taille taille, */
void afficher_tab_opera (struct opera *tab[], int taille) {
	int i;
	for (i = 0; i < taille; i ++) {
		afficher_opera(tab[i]);
		printf("\n");
	}
}

/** Fonction qui initiale un tableau d'opéras avec les opéras */
/* stockés dans le fichier de nom n_fich */
/* et renvoie l'adresse ainsi initialisé */
/* (l'entier pointé par le 2e paramètre d'entrée */
/* prend la valeur du nombre d'opéras référencés dans le tableau initialisé) */
struct opera ** initialiser_tab_opera_fichier (char *n_fich, int * taille) {
	int i;
  FILE * f;
  struct opera ** tab_res;
  struct opera * op = allouer_opera();
  /** Ouverture du fichier de nom n_fich en lecture */
	if ((f=fopen(n_fich,"r")) == NULL) {
		fprintf(stderr, "fichier %s introuvable \n", n_fich);
		exit(EXIT_FAILURE);
	}
	fscanf(f,"%d\n", taille);
  /* et stockage de son contenu dans le tableau tab_operas */
  tab_res = allouer_tab_opera(*taille);
	/* On suppose que les titres, villes de création et noms et prénoms */
  /* des compositeurs des opéras du fichier ENTREE ont au plus TAILLE_MAX caractères */
	op->titre = allouer_chaine(TAILLE_MAX);
	op->date_creation = allouer_date();
	op->ville_creation = allouer_chaine(TAILLE_MAX);
	op->compositeur = allouer_individu();
	op->compositeur->nom = allouer_chaine(TAILLE_MAX);
	op->compositeur->prenom = allouer_chaine(TAILLE_MAX);
	op->compositeur->naissance = allouer_date();
	op->compositeur->origine = allouer_chaine(TAILLE_MAX);
	/* récupération des opéras stockés dans le fichier */
	for (i = 0; i < *taille; ++i) {
		fscanf(f,"%s\n", op->titre);
		fscanf(f,"créé le %u/%u/%u à %s\n", &op->date_creation->jour, &op->date_creation->mois, &op->date_creation->annee, op->ville_creation);
		fscanf(f,"%s %s né le %u/%u/%u à %s\n", op->compositeur->prenom, op->compositeur->nom, &op->compositeur->naissance->jour, &op->compositeur->naissance->mois,&op->compositeur->naissance->annee, op->compositeur->origine);
    tab_res[i] = allouer_opera();
    tab_res[i]->titre = allouer_chaine(strlen(op->titre));
    strcpy(tab_res[i]->titre, op->titre);
    tab_res[i]->date_creation = allouer_date();
    *(tab_res[i]->date_creation) = *(op->date_creation);
    tab_res[i]->ville_creation = allouer_chaine(strlen(op->ville_creation));
    strcpy(tab_res[i]->ville_creation, op->ville_creation);
    tab_res[i]->compositeur = allouer_individu();
    tab_res[i]->compositeur->nom = allouer_chaine(strlen(op->compositeur->nom));
    strcpy(tab_res[i]->compositeur->nom, op->compositeur->nom);
    tab_res[i]->compositeur->prenom = allouer_chaine(strlen(op->compositeur->prenom));
    strcpy(tab_res[i]->compositeur->prenom, op->compositeur->prenom);
    tab_res[i]->compositeur->origine = allouer_chaine(strlen(op->compositeur->origine));
    strcpy(tab_res[i]->compositeur->origine, op->compositeur->origine);
    tab_res[i]->compositeur->naissance = allouer_date();
    *(tab_res[i]->compositeur->naissance) = *(op->compositeur->naissance);
	}
	detruire_opera(&op);
  /* fermeture du fichier */
  fclose(f);
  return tab_res;
}

/** Fonction qui sauvegarde un tableau d'opéras t de taille n */
/* dans le fichier de nom n_fich */
void sauvegarder_tab_opera_fichier (struct opera **t, int n, char *n_fich) {
	int i;
	FILE *f ;
	if ((f=fopen(n_fich,"w")) == NULL) {
		fprintf(stderr, "ouverture fichier %s impossible \n", n_fich);
		exit(EXIT_FAILURE);
	}
	fprintf(f, "%d\n", n);
	for (i = 0; i < n; ++i) {
		fprintf(f, "%s\n", t[i]->titre);
		fprintf(f, "créé le %u/%u/%u à %s\n", t[i]->date_creation->jour, t[i]->date_creation->mois, t[i]->date_creation->annee, t[i]->ville_creation);
		fprintf(f, "%s %s né le %u/%u/%u à %s\n", t[i]->compositeur->prenom, t[i]->compositeur->nom, t[i]->compositeur->naissance->jour, t[i]->compositeur->naissance->mois, t[i]->compositeur->naissance->annee, t[i]->compositeur->origine);
	}
	fclose(f);
}
