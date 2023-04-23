/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <time.h> /* pour le temps */

/* declaration constantes et types utilisateurs */
typedef int item;
/* declaration de fonctions utilisateurs */
int saisir_entier (int vmin, int vmax);
void initialiser_alea_tab (item *tab, int taille);
void afficher_tab(item *tab, int taille);
int pos_min_tab(item *tab, int n);
int pos_max_tab(item *tab, int n);
item max_diff_tab(item *tab, int taille);
int max3(int x, int y, int z);
/* fonction principale */
int main()
{
    /* declaration et initialisation des variables */
    int n;
    /* ici faire quelque chose */
    srand (time (NULL));
    n = saisir_entier(0,100);
    item * tab = malloc(sizeof(int)*n);
    initialiser_alea_tab(tab, n);
    printf("Voici le tableau : ");
    afficher_tab(tab, n);
    printf("Le minimum du tableau est %d\n", *(tab+pos_min_tab(tab, n)));
    printf("Le maximum du tableau est %d\n", *(tab+pos_max_tab(tab, n)));
    printf("Le maximum de la différence du tableau est %d\n", max_diff_tab(tab, n));
    free(tab);
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
int saisir_entier (int vmin, int vmax) {
  int res, n;
  char c;
  do {
    printf("Tapez une valeur entière comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    if (0 == n) {
			do { scanf("%c", &c); }
			while (c != ' ' && c != '\t' && c != '\n');
		}
    printf("T'es bêtes ou quoi ???? 🤣🫵\n");
  }
  while (1);
}

void initialiser_alea_tab (item *tab, int taille) 
{
  for (int i = 0; i < taille; ++i) 
  {
    *(tab+i) = rand()%100;
  }
}

void afficher_tab(item *tab, int taille) {
  for (int i = 0; i < taille; ++i) { 
    printf("%d ", *(tab+i)); 
  }
  printf("\n");
}


int pos_min_tab(item *tab, int n)
{
  int pos_min = 0;
  for (int  i = 1; i < n; ++i)
  {
    if ((*(tab+i)) < (*(tab+pos_min)))
    {
      pos_min = i;
    }
  }
  return pos_min;
}

int pos_max_tab(item *tab, int n)
{
  int pos_max = 0;
  for (int  i = 1; i < n; ++i)
  {
    if ((*(tab+i)) > (*(tab+pos_max)))
    {
      pos_max = i;
    }
  }
  return pos_max;
}

item max_diff_tab(item *tab, int taille)
{
  int milieu = taille/2, pos_min_deb, pos_max_fin;
  item max_fin_min_deb, max_diff_deb, max_diff_fin;
  if (taille <= 1) { return 0; }
  max_diff_deb = max_diff_tab(tab, milieu);
  max_diff_fin = max_diff_tab(tab+milieu, taille-milieu);
  pos_min_deb = pos_min_tab(tab, milieu);
  pos_max_fin = pos_max_tab(tab+milieu, taille-milieu);

  max_fin_min_deb = *(tab+pos_max_fin+milieu) - *(tab+pos_min_deb);

  return max3(max_diff_deb, max_diff_fin, max_fin_min_deb);
}

int max3(int x, int y, int z)
{
  if ((x > y) && (y > z))
  {
    return x;
  }

  if ((x < y) && (y < z))
  {
    return z;
  }
  
  return y;
}
