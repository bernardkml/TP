/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <time.h> /* pour le temps */

/* declaration constantes et types utilisateurs */
typedef int item;
typedef struct matrice {
        int nb_lignes;
        int nb_colonnes;
        item coeff [10][10];
} matrice;

/* declaration de fonctions utilisateurs */
int saisir_entier (int vmin, int vmax);
void initialiser_alea_mat (struct matrice *am);
void afficher_mat(const struct matrice *am);
void transposer_mat(struct matrice *am_t, const struct matrice *am);
void reduire_mat (struct matrice *am);
/* fonction principale */
int main()
{
    /* declaration et initialisation des variables */
    matrice am, am_t; 
    /* ici faire quelque chose */
    srand(time(NULL));
    am.nb_colonnes = saisir_entier(0,9);
    am.nb_lignes = saisir_entier(0,9);
    initialiser_alea_mat(&am);
    printf("Matrice avant transposition :\n");
    afficher_mat(&am);
    transposer_mat(&am_t,&am);
    printf("Matrice après transposition :\n");
    afficher_mat(&am_t);
    reduire_mat(&am);
    printf("Matrice après réduction :\n");
    afficher_mat(&am);
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */

/** Fonction qui saisit et renvoie un entier compris entre vmin et vmax */
int saisir_entier (int vmin, int vmax) {
  int res, n;
  char c;
  do {
    printf("Tapez une valeur entière comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    if (0 == n) {
			do { 
            scanf("%c", &c); 
            } while (c != ' ' && c != '\t' && c != '\n');
		}
    printf("T'es bêtes ou quoi ???? 🤣🫵\n");
  }
  while (1);
}

void initialiser_alea_mat (struct matrice *am)
{
    for (int i = 0; i < am->nb_colonnes; ++i)
    {
        for (int j = 0; j < am->nb_lignes; ++j)
        {
            *(*(am->coeff+i)+j) = rand()%100;
        }
    } 
}

void afficher_mat(const struct matrice *am) 
{
    for (int i = 0; i < am->nb_lignes; ++i)
    {
        for (int j = 0; j < am->nb_colonnes; ++j)
        {
            printf("%d ",am->coeff[i][j]);
        }
        printf("\n");
    } 
}

void transposer_mat(struct matrice *am_t, const struct matrice *am)
{
    am_t->nb_colonnes = am->nb_lignes;
    am_t->nb_lignes = am->nb_colonnes;

    for (int i = 0; i < am->nb_colonnes; ++i)
    {
        for (int j = 0; j < am->nb_lignes; ++j)
        {
            *(*(am_t->coeff+j)+i) = *(*(am->coeff+i)+j);
        }
    }
}

void reduire_mat (struct matrice *am)
{
    am->nb_lignes--;
    am->nb_colonnes--;

    for (int i = 0; i < am->nb_colonnes; ++i)
    {
        for (int j = 0; j < am->nb_lignes; ++j)
        {
            *(*(am->coeff+i)+j) = *(*(am->coeff+i+1)+j+1);
        }
    }
}
