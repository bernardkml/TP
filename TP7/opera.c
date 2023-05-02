/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <string.h>



/* declaration constantes et types utilisateurs */ 
#define TAILLE_MAX 17 /* pour la fonction initialiser_tab_operas_fichier */
#define ENTREE argv[1] /* Nom du fichier pour initialiser le tableau d'adresses d'opÃ©ras */
struct date {
	unsigned jour;
	unsigned mois;
	unsigned annee;
};

struct individu {
		char * nom;
		char * prenom;
		struct date * naissance;
};

struct opera {
	char * titre; /* le titre de l'opÃ©ra */
	struct date * date_creation; /* l'annÃ©e de la crÃ©ation (i.e. de la premiÃ¨re reprÃ©sentation) */
	char * ville_creation; /* ville de la crÃ©ation (i.e. de la premiÃ¨re reprÃ©sentation) */
	struct individu * compositeur; /* nom du compositeur */
};


/* declaration de fonctions utilisateurs */
int age_revolu (const struct individu * ind, const struct date * d);
void echanger_opera (struct opera **op1, struct opera **op2);
void afficher_opera (const struct opera * op);
void recherche_tab_opera_age (struct opera *tab[], int taille, int a);
void trier_tab_opera_creation (struct opera *tab[], int taille);
int comparer_date(const struct date * d1, const struct date * d2);
int reorganiser_tab_opera_ville (struct opera * tab[], int taille, const char * v);
struct opera ** initialiser_tab_opera_fichier (char *n_fich, int * taille);
void afficher_date(const struct date * d);
void afficher_individu (const struct individu * ind);
void detruire_individu (struct individu ** ind);
void detruire_opera (struct opera ** op);
int recherche_pos_opera_ancien (struct opera *tab[], int taille);
struct opera * allouer_opera (void);
struct opera ** allouer_tab_opera (int taille);
char * allouer_chaine (int n);
struct date * allouer_date (void);
struct individu * allouer_individu (void);
void recherche_dicho_tab_opéra(const struct opera * tab, int n, int a);
int main()
{
    /* declaration et initialisation des variables */
    int  n = TAILLE_MAX;
    struct opera ** tab =  initialiser_tab_opera_fichier("Operas_entree.txt",&n);
    /* ici faire quelque chose */
	printf("Affichages des Opéras : \n\n");
    for (int i = 0; i < n; ++i)
    {
        afficher_opera(tab[i]);
        printf("\n\n");
    }
	printf("Affichage des Opéras avant que leur compositeur est 40 piges révolus: \n\n");
	recherche_tab_opera_age(tab, n, 40);
	for (int l = 0; l < n; ++l)
    {
        afficher_opera(tab[l]);
        printf("\n\n");
    }
	printf("Affichage après avoir réordonné le tableau selon l'odre chronologiqe des créations: \n\n");
	trier_tab_opera_creation(tab,n);
	for (int j = 0; j < n; j++)
	{
		afficher_opera(tab[j]);
		printf("\n\n");
	}
	printf("Affichage des Opéras après avoir placé tous les operas créé a Paris au début du tableau: \n\n");
	reorganiser_tab_opera_ville(tab, n, "Paris");
	for (int k = 0; k < n; k++)
	{
		afficher_opera(tab[k]);
		printf("\n\n");
	}

	detruire_opera(tab);
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
/** Fonction qui affiche le titre, le prÃ©nom et le nom du compositeur, (la date et la ville de crÃ©ation) de l'opÃ©ra op */
void afficher_opera (const struct opera * op) {
	afficher_individu(op->compositeur);
	printf(", %s (", op->titre);
	afficher_date(op->date_creation);
	printf(", %s)", op->ville_creation);
}

/** Fonction qui affiche les valeurs des champs de la date passÃ©e en argument */
void afficher_date(const struct date * d) {
	printf("%u/%u/%u", d->jour, d->mois, d->annee);
}

/* Fonction qui affiche le prÃ©nom, le nom et la date de naissance de l'individu pointÃ© par ind */
void afficher_individu (const struct individu * ind) {
	printf("%s %s (", ind->prenom, ind->nom);
	afficher_date(ind->naissance);
	printf(")");
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

/** Fonction qui affiche tous les opÃ©ras du tableau tab, de taille taille, */
/* crÃ©Ã©s avant que leur compositeur ait a annÃ©es rÃ©volues */
/** ComplexitÃ© : \Theta(N) si N est la taille du tableau */
void recherche_tab_opera_age (struct opera *tab[], int taille, int a) {
	int i, a_revolu, trouve = 0;
	for (i = 0; i < taille; i ++) {
		if ( (a_revolu = age_revolu(tab[i]->compositeur, tab[i]->date_creation)) < a ) {
			trouve = 1;
			afficher_opera(tab[i]);
			printf("[%s avait %d ans]\n", tab[i]->compositeur->nom, a_revolu);
		}
	}
	if (!trouve)
		printf("Aucun opÃ©ra crÃ©Ã© avant que son compositeur ait %d annÃ©es rÃ©volues\n", a);
}


/** Fonction qui trie le tableau d'opÃ©ras tab, de taille taille, */
/* selon l'ordre chronologique de crÃ©ation (tri par sÃ©lection) */
/** ComplexitÃ© : \Theta(N^2) si N est la taille du tableau */
void trier_tab_opera_creation (struct opera *tab[], int taille) {
  int i;
  int pos_opera_ancien;
  for(i = 0; i < taille-1; i ++){
    pos_opera_ancien = recherche_pos_opera_ancien(tab + i, taille - i);
    echanger_opera(&tab[i], &tab[i + pos_opera_ancien]);
  }
}



/** Fonction qui renvoie -1 si d1 est antÃ©rieure Ã  d2, */
/**          qui renvoie 1 si d1 est postÃ©rieure Ã  d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date * d1, const struct date * d2) {
	if(d1->annee < d2->annee)
		return -1;
	if (d1->annee > d2->annee)
		return 1;
	if (d1->mois < d2->mois)
		return -1;
	if (d1->mois > d2->mois)
		return 1;
	if (d1->jour < d2->jour)
		return -1;
	if (d1->jour > d2->jour)
		return 1;
	return 0;
}

/** Variante */
/** ComplexitÃ© : \Theta(N) si N est la taille du tableau */

int reorganiser_tab_opera_ville (struct opera * tab[], int taille, const char * v) {
	int i, j;
	for (j = 0; j < taille && !strcmp(v, tab[j]->ville_creation); j ++);
	for (i = j + 1; i < taille; i ++) {
		if (!strcmp(v, tab[i]->ville_creation)) {
			echanger_opera (&tab[i], &tab[j]);
			j ++;
		}
	}
	return j;
}

/** Fonction qui Ã©change les adresses d'opÃ©ra pointÃ©es par les deux arguments */
void echanger_opera (struct opera **op1, struct opera **op2) {
	struct opera *temp = *op1;
	*op1 = *op2;
	*op2 = temp;
}

/** Fonction qui initiale un tableau d'opÃ©ras avec les opÃ©ras */
/* stockÃ©s dans le fichier de nom n_fich */
/* et renvoie l'adresse ainsi initialisÃ© */
/* (l'entier pointÃ© par le 2e paramÃ¨tre d'entrÃ©e */
/* prend la valeur du nombre d'opÃ©ras rÃ©fÃ©rencÃ©s dans le tableau initialisÃ©) */
struct opera ** initialiser_tab_opera_fichier (char *n_fich, int * taille) {
	int i;
  FILE * f;
  struct opera ** tab_res;
  struct opera * op = allouer_opera();
  /** Ouverture du fichier de nom n_fich en lecture */
	if ((f=fopen(n_fich,"r")) == 0) {
		exit(EXIT_FAILURE);
	}
	fscanf(f,"%d\n", taille);
  /* et stockage de son contenu dans le tableau tab_operas */
  tab_res = allouer_tab_opera(*taille);
	/* On suppose que les titres, villes de crÃ©ation et noms et prÃ©noms */
  /* des compositeurs des opÃ©ras du fichier ENTREE ont au plus TAILLE_MAX caractÃ¨res */
	op->titre = allouer_chaine(TAILLE_MAX);
	op->date_creation = allouer_date();
	op->ville_creation = allouer_chaine(TAILLE_MAX);
	op->compositeur = allouer_individu();
	op->compositeur->nom = allouer_chaine(TAILLE_MAX);
	op->compositeur->prenom = allouer_chaine(TAILLE_MAX);
	op->compositeur->naissance = allouer_date();
	/* rÃ©cupÃ©ration des opÃ©ras stockÃ©s dans le fichier */
	for (i = 0; i < *taille; i++) {
		fscanf(f,"%s\n", op->titre);
		fscanf(f,"%u/%u/%u %s\n", &op->date_creation->jour, &op->date_creation->mois, &op->date_creation->annee, op->ville_creation);
		fscanf(f,"%s %s (%u/%u/%u)\n", op->compositeur->prenom, op->compositeur->nom, &op->compositeur->naissance->jour, &op->compositeur->naissance->mois,&op->compositeur->naissance->annee);
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
    tab_res[i]->compositeur->naissance = allouer_date();
    *(tab_res[i]->compositeur->naissance) = *(op->compositeur->naissance);
	}
	detruire_opera(&op);
  /* fermeture du fichier */
  fclose(f);
  return tab_res;
}

/** Fonction qui libÃ¨re toute la mÃ©moire occupÃ©e par l'individu pointÃ© par ind */
void detruire_individu (struct individu ** ind) {
	free((*ind)->nom);
	free((*ind)->prenom);
	free((*ind)->naissance);
  free(*ind);
  *ind = 0;
}

/** Fonction qui libÃ¨re toute la mÃ©moire occupÃ©e par l'opÃ©ra pointÃ© par op */
void detruire_opera (struct opera ** op) {
	free((*op)->titre);
	free((*op)->ville_creation);
	free((*op)->date_creation);
	detruire_individu(&(*op)->compositeur);
	free(*op);
  *op = 0;
}

/** Fonction qui renvoie la position de l'opÃ©ra le plus anciennement crÃ©Ã© dans le tableau d'opÃ©ras tab */
/** ComplexitÃ© : \Theta(N) si N est la taille du tableau */
int recherche_pos_opera_ancien (struct opera *tab[], int taille) {
	int i;
  int pos_opera_ancien = 0;
  for(i = 1; i < taille; i ++) {
    if ( comparer_date(tab[i]->date_creation,tab[pos_opera_ancien]->date_creation) < 0)
      pos_opera_ancien = i;
  }
  return pos_opera_ancien;
}

/** Fonction qui alloue de l'espace sur le tas pour un opÃ©ra */
/* et renvoie l'adresse du bloc allouÃ© */
struct opera * allouer_opera (void) {
		struct opera * op = malloc(sizeof(struct opera));
		if (op == 0) {
			perror("Ã‰chec allocation opÃ©ra");
			exit(EXIT_FAILURE);
		}
		return op;
}

/** Fonction qui crÃ©e et renvoie l'adresse d'un tableau d'opÃ©ras de taille taille */
struct opera ** allouer_tab_opera (int taille) {
	int i;
	struct opera ** res = malloc (sizeof(struct opera *) * taille);
	for (i = 0; i < taille; i ++)
		res[i] = allouer_opera();
	return res;
}

/** Fonction qui alloue de l'espace sur le tas pour une chaÃ®ne de n caractÃ¨res */
/** et renvoie l'adresse du bloc, de taille n+1, allouÃ© */
char * allouer_chaine (int n) {
  char *str = malloc((n+1)*sizeof(char));
	if (str == 0) {
		perror("Ã‰chec allocation chaine de caractÃ¨res (struct individu ou ville)");
		exit(EXIT_FAILURE);
	}
  return str;
}

/** Fonction qui alloue de l'espace sur le tas pour une date */
/** et renvoie l'adresse du bloc allouÃ© */
struct date * allouer_date (void) {
	struct date * d = malloc(sizeof(struct date));
	if (d == 0) {
		perror("Ã‰chec allocation struct date");
		exit(EXIT_FAILURE);
	}
  return d;
}

/** Fonction qui alloue de l'espace sur le tas pour un individu */
/** et renvoie l'adresse du bloc allouÃ© */
struct individu * allouer_individu (void) {
  struct individu * ind = malloc(sizeof(struct individu));
	if (ind == 0) {
		perror("Ã‰chec allocation struct individu");
		exit(EXIT_FAILURE);
	}
  return ind;
}

//void recherche_dicho_tab_opéra(const struct opera * tab, int n, int a)
//{
//	if (n <= 0)
//	{
//		printf("T'es bêtes ou quoi ?\n");
//	} 
//	switch (tab->date_creation->annee == a)
//	{
//	case 1:
//		afficher_opera(tab);
//		break;
//	
//	default:
//		recherche_dicho_tab_opéra(tab+1,n-1,a);
//		break;
//	} 
//	printf("Y'a aps !\n");
//

//}