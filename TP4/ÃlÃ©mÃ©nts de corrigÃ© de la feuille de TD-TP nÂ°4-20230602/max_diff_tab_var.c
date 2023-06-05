/* declaration de fonctionnalites supplementaires */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define N 10000

typedef int item;

item pos_max_tab (item *, int);
item pos_min_tab (item *, int);
item max_trois (item, item, item);
item max_diff_tab (item *, int);
item max_diff_tab_iter (item *, int deb, int fin);
item saisie_item (item, item);
void affiche_tab (item *, int);

int main ()
{
  int i, taille = saisie_item(0,N);
  item tab[N];
  srand(time(NULL));
  for (i = 0; i < taille; ++i)
  {
    tab[i] = rand()%1000;
  }
  if (taille <= 30)
    affiche_tab(tab, taille);
  printf("Valeur maximale du tableau : %d \n", *(tab + pos_max_tab(tab, taille)));
  printf("Valeur minimale du tableau : %d \n", *(tab + pos_min_tab(tab, taille)));
  printf("Écart maximal entre deux valeurs du tableau (récursif) : %d \n", max_diff_tab(tab, taille));
  printf("Écart maximal entre deux valeurs du tableau (itératif) : %d \n", max_diff_tab_iter(tab, 0, taille-1));

  return EXIT_SUCCESS;
}

int pos_max_tab (item * tab, int taille)
{
  int i, pos_max;
  item max_tab;
  if (taille <= 0) {
    perror("Erreur ! Recherche du max dans un tableau vide.\n");
    exit(2);
  }
  pos_max = 0;
  max_tab = *tab;
  for (i = 1; i < taille; ++i)
    if (*(tab+i) > max_tab)
    {
      pos_max = i;
      max_tab = *(tab+i);
    }
  return pos_max;
}

int pos_min_tab (item * tab, int taille)
{
  int i, pos_min;
  item min_tab;
  if (taille <= 0) {
    perror("Erreur ! Recherche du min dans un tableau vide.\n");
    exit(2);
  }
  pos_min = 0;
  min_tab = *tab;
  for (i = 1; i < taille; ++i)
    if (*(tab+i) < min_tab)
    {
      pos_min = i;
      min_tab = *(tab+i);
    }
  return pos_min;
}

item max_trois (item x, item y, item z)
{
  if (x < y)
    return y < z ? z : y;
  return x < z ? z : x;
}

/** Returns max {t[j] - t[i] | deb ≤ i ≤ j ≤ fin } (NON RECURSIVE version) */
/** Requires \Omega(n^2) comparisons of items in the worst case */
item max_diff_tab_iter (item *t, int deb, int fin)
{
  int i, j;
  item res = 0;
  for (i = deb; i <= fin; ++i)
    for (j = i+1; j <= fin; ++j)
      if (t[j]-t[i] > res)
        res = t[j]-t[i];
  return res;
}

/** Returns max {t[j] - t[i] | 0 ≤ i ≤ j ≤ taille-1 } (RECURSIVE version) */
/** Requires O(n \log n) comparisons of items in the worst case */
/** (Feuille de TD-TP n°4, exercices 1 et 3)) */
item max_diff_tab (item *tab, int taille)
{
  int m = taille/2, pos_min_deb, pos_max_fin;
  item max_fin_min_deb, max_diff_deb, max_diff_fin;
  if (taille <= 1)
    return 0;
  max_diff_deb = max_diff_tab(tab, m);
  max_diff_fin = max_diff_tab(tab + m, taille - m);
  pos_max_fin = pos_max_tab(tab + m, taille - m);
  pos_min_deb = pos_min_tab(tab, m);
  max_fin_min_deb = *(tab + pos_max_fin + m) - *(tab + pos_min_deb);
  return max_trois(max_diff_deb, max_diff_fin, max_fin_min_deb);
}

void affiche_tab (item *tab, int taille)
{
  int i;
  for (i = 0; i <taille; ++i)
    printf("%5d", *(tab+i));
  printf("\n");
}

int saisie_item (int vmin, int vmax) {
  int res, n;
  char c;
  do
  {
    printf("Tapez une valeur entière comprise entre %d et %d : ", vmin, vmax);
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
