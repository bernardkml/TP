/* Ce programme lit une taille (un entier positif inférieur à 1000) */
/* entrée au clavier par l'utilisateur, */
/* initialise "pseudo-aléatoirement" un tableau d'entiers de cette taille et l'affiche, */
/* puis calcule et affiche */
/*  - le maximum du tableau ;
/*  - le minimum du tableau ;
/*  - le maximum de la différence b - a entre deux valeurs a et b du tableau */
/*    (avec b "à droite" de a dans le tableau) */
/* N.B. Ce dernier calcul est fait de deux façons, itérativement et récursivement */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define N 10000

typedef int item;

item max_tab (item[], int, int);
item min_tab (item[], int, int);
item max_trois (item, item, item);
item max_diff_tab (item[], int, int);
item max_diff_tab_rec (item[], int, int);
item saisie_item (item, item);
void affiche_tab (item[], int, int);

int main ()
{
  int i, taille = saisie_item(0,N);
  item t[N];
  /* on initialise le tableau en faisant appel au générateur pseudo-aléatoire */
  srand(time(NULL));
  for (i = 0; i < taille; ++i)
  {
    t[i] = rand()%1000;
  }
  if (taille <= 30)
    affiche_tab(t, 0, taille-1);
  printf("Valeur maximale du tableau : %d \n", max_tab(t, 0, taille-1));
  printf("Valeur minimale du tableau : %d \n", min_tab(t, 0, taille-1));
  printf("Écart maximal (méthode itérative): %d \n", max_diff_tab(t, 0, taille-1));
  printf("Écart maximal (méthode récursive): %d \n", max_diff_tab_rec(t, 0, taille-1));

  return EXIT_SUCCESS;
}

/** Renvoie max {t[i] | deb ≤ i ≤ fin } */
/** Requiert n-1 comparaisons de valeurs */
item max_tab (item t[], int deb, int fin)
{
  int i;
  item res;
  if (fin < deb)
    return INT_MIN;
  res = t[deb];
  for (i = deb+1; i <= fin; ++i)
  {
    if (t[i] > res)
      res = t[i];
  }
  return res;
}

/** Renvoie min {t[i] | deb ≤ i ≤ fin } */
/** Requiert n-1 comparaisons de valeurs */
item min_tab (item t[], int deb, int fin)
{
  int i;
  item res;
  if (fin < deb)
    return INT_MAX;
  res = t[deb];
  for (i = deb+1; i <= fin; ++i)
  {
    if (t[i] < res)
      res = t[i];
  }
  return res;
}

/** Renvoie max {t[j] - t[i] | deb ≤ i ≤ j ≤ fin } (version ITÉRATIVE) */
/** Requiert \Omega(n^2) comparaisons de valeurs dans le cas le plus défavorable */
item max_diff_tab (item t[], int deb, int fin)
{
  int i, j;
  item res = 0;
  for (i = deb; i <= fin; ++i)
    for (j = i+1; j <= fin; ++j)
      if (t[j]-t[i] > res)
        res = t[j]-t[i];
  return res;
}

/* Renvoie le maximum de trois valeurs entières */
item max_trois (item x, item y, item z)
{
  if (x < y)
    return y < z ? z : y;
  return x < z ? z : x;
}

/** Renvoie max {t[j] - t[i] | deb ≤ i ≤ j ≤ fin } (version RÉCURSIVE) */
/** Requiert O(n \log n) comparaisons de valeurs dans le cas le plus défavorable */
item max_diff_tab_rec (item t[], int deb, int fin)
{
  int m = (deb+fin)/2;
  item max_fin_min_deb, max_diff_deb, max_diff_fin;
  if (fin <= deb)
    return 0;
  /* calcul de max {t[j] - t[i] | deb ≤ i ≤ j ≤ m } */
  /* (rappel récursif sur la moitié "gauche" du tableau) */
  max_diff_deb = max_diff_tab_rec(t, deb, m);
  /* calcul de max {t[j] - t[i] | m+1 ≤ i ≤ j ≤ fin } */
  /* rappel récursif sur la partie "droite" du tableau */
  max_diff_fin = max_diff_tab_rec(t, m+1, fin);
  /* calcul de max {t[j] - t[i] | deb ≤ i ≤ m et m+1 ≤ j ≤ fin } */
  max_fin_min_deb = max_tab(t, m+1, fin) - min_tab(t, deb, m);
  return max_trois(max_diff_deb, max_diff_fin, max_fin_min_deb);
}

/* Affiche les valeurs d'un tableau */
void affiche_tab (item t[], int deb, int fin)
{
  int i;
  for (i = deb; i <= fin; ++i)
    printf("%5d", t[i]);
  printf("\n"); /* ou putchar('\n'); */
}

/* Lit une valeur entière entrée au clavier par l'utilisateur */
/* et renvoie cette valeur si elle est comprise entre vmin et vmax */
/* (Dans le cas contraire, demande à l'utilisateur de recommencer) */
int saisie_item (int vmin, int vmax) {
  int res, n;
  char c;
  do
  {
    printf("Tapez une valeur entière comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    /* si la lecture d'une valeur entière a échoué... */
    if (0 == n)
    {
      /* ...on "avale" la fin de la chaîne entrée au clavier par l'utilisateur */
      /* avant de lui demander de recommencer */
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
