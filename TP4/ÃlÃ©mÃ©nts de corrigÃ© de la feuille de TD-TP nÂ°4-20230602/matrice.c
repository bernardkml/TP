#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef int item;

struct matrice {
  int nb_lignes;
  int nb_colonnes;
  item coeff[N][N];
};

int saisir_entier (int, int);
void initialiser_alea_mat (struct matrice *);
void afficher_mat (const struct matrice *);
void transposer_mat (struct matrice *, const struct matrice *);
void reduire_mat (struct matrice *);

item main () {

  struct matrice m, m_t;

  /* Initialisation et affichage de la matrice m */
  printf("Saisie du nombre de lignes de la matrice\n");
  m.nb_lignes = saisir_entier(0, 9);
  printf("Saisie du nombre de colonnes de la matrice\n");
  m.nb_colonnes = saisir_entier(0, 9);
  srandom(time(NULL));
  initialiser_alea_mat (&m);
  printf("Affichage de la matrice\n");
  afficher_mat (&m);
  /* Vérification des évaluations de la question 1 de la feuille de TD n°5 */
  printf("Test des évaluations de la question 1 du TD \n");
  printf("m.coeff = %p, \t m.coeff[0] = %p, \t m.coeff[1]= %p \n", m.coeff, m.coeff[0], m.coeff[1]);
  /* Affichage de la transposée de la matrice m */
  transposer_mat (&m_t, &m);
  printf("Affichage de la transposée\n");
  afficher_mat (&m_t);
  /* Affichage de la réduite de la matrice m */
  reduire_mat (&m);
  afficher_mat (&m);

  return EXIT_SUCCESS;
}

/** Fonction qui initialise "au hasard", pour la matrice pointée par am */
/* - les coefficients (des entiers compris entre 0 et 99) */
void initialiser_alea_mat (struct matrice * am) {
  int i,j;
  for (i = 0; i < am->nb_lignes; ++i)
    for (j = 0; j < am->nb_colonnes; ++j)
      *( *(am->coeff + i) + j) = random()%100;
}

/** Fonction qui affiche la matrice pointée par am, ligne par ligne */
void afficher_mat (const struct matrice *am) {
  int i,j;
  for (i = 0; i < am->nb_lignes; ++i) {
    for (j = 0; j < am->nb_colonnes; ++j)
      printf("%5d", *( *(am->coeff + i) + j));
    printf("\n");
  }
  printf("\n");
}

/** Fonction qui supprime la 1re ligne et la 1re colonne */
/* de la matrice pointée par am */
void reduire_mat (struct matrice * am) {
  int i,j;
  --am->nb_lignes;
  --am->nb_colonnes;
  for (i = 0; i < am->nb_lignes; ++i)
    for (j = 0; j < am->nb_colonnes; ++j)
      *( *(am->coeff + i) + j) = *( *(am->coeff + i + 1) + j + 1);
}

/** Fonction qui transpose la matrice pointée par am */
/* dans la matrice pointée par am_t */
void transposer_mat (struct matrice *am_t, const struct matrice *am) {
  int i,j;
  am_t->nb_lignes = am->nb_colonnes;
  am_t->nb_colonnes = am->nb_lignes;
  for (i = 0; i < am_t->nb_lignes; ++i)
    for (j = 0; j < am_t->nb_colonnes; ++j)
      *( *(am_t->coeff + i) + j) = *( *(am->coeff + j) + i);
}

int saisir_entier (int vmin, int vmax) {
  int res, n;
  char c;
  do
  {
    printf("Tapez un entier compris entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    if (0 == n)
    {
			do
      {
				scanf("%c", &c);
			}
			while (c != ' ' && c != '\t' && c != '\n');
		}
    printf("Erreur ! Recommencez !");
  }
  while (1);
}
