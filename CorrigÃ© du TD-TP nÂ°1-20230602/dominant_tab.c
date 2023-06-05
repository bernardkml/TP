/* Ce programme lit une taille (un entier positif inférieur à 1000) */
/* entrée au clavier par l'utilisateur, */
/* initialise "pseudo-aléatoirement" un tableau d'entiers de cette taille et l'affiche, */
/* puis recherche une valeur dominante dans le tableau et affiche */
/*  - la valeur dominante du tableau si une telle valeur existe ;
/*  - ou un message indiquant qu'uen valeur n'est dominante dans le tableau */
/* N.B. La recherche est faite de deux façons, itérativement et récursivement */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define N 10000

typedef int item;

int dominant_tab (item[], int, int);
int dominant_tab_rec (item[], int, int);
int saisie_entier (int, int);
void affiche_tab (item[], int, int);

int main ()
{
  int i, taille = saisie_entier(0,N), ind_dominant;
  item t[N];
  /* on initialise le tableau en faisant appel au générateur pseudo-aléatoire */
  srand(time(NULL));
  for (i = 0; i < taille; ++i)
  {
    t[i] = rand()%3;
  }
  if (taille <= 30)
    affiche_tab(t, 0, taille-1);

  /* Détection itérative d'une valeur dominante dans t */
  printf("Valeur dominante du tableau (méthode itérative): \n");
  ind_dominant = dominant_tab(t, 0, taille-1);
  if (ind_dominant < 0)
    printf("Aucune valeur n'est dominante dans le tableau \n");
  else
    printf("La valeur %d est dominante dans le tableau \n", t[ind_dominant]);

  /* Détection récursive d'une valeur dominante dans t */
  printf("Valeur dominante du tableau (méthode récursive): \n");
  ind_dominant = dominant_tab_rec(t, 0, taille-1);
  if (ind_dominant < 0)
    printf("Aucune valeur n'est dominante dans le tableau \n");
  else
    printf("La valeur %d est dominante dans le tableau \n", t[ind_dominant]);

  return EXIT_SUCCESS;
}

/** Renvoie un indice de la valeur dominante entre les indices deb et fin */
/* si une telle valeur existe, */
/* renvoie -1 dans le cas contraire (version ITÉRATIVE)*/
/** Requiert \Omega(n^2) comparaisons de valeurs dans la cas le plus défavorable */
int dominant_tab (item t[], int deb, int fin)
{
  int i, j, cpt, n = fin-deb+1, m = (deb+fin)/2;
  for (i = deb; i <= m; ++i)
  {
    cpt = 1;
    for (j = i+1; j <= fin; ++j)
    {
      if (t[i] == t[j])
        ++cpt;
    }
    if (cpt >= n/2 + 1)
      return i;
  }
  return -1;
}

/** Renvoie un indice de la valeur dominante entre les indices deb et fin */
/* si une telle valeur existe, */
/* renvoie -1 dans le cas contraire (version RÉCURSIVE)*/
/** Requiert O(n \log n) comparaisons de valeurs dans la cas le plus défavorable */
int dominant_tab_rec (item t[], int deb, int fin)
{
  int i, k, cpt, m = (deb+fin)/2, n = fin-deb+1;
  if (fin < deb) return -1;
  if (fin == deb) return deb;
  /* recherche d'une valeur dominante entre les indices deb et m du tableau */
  /* (rappel récursif sur la moitié "gauche" du tableau) */
  k = dominant_tab_rec(t, deb, m);
  /* si une valeur dominante a été trouvée dans la moitié "gauche"... */
  if (k >= deb)
  {
    cpt = 0;
    /* ... on regarde si elle est dominante dans le tableau entier */
    for(i = deb; i <= fin; ++i)
    {
      if (t[i] == t[k])
        ++cpt;
    }
    /* si la valeur est dominante dans le tableau entier... */
    if (cpt >= n/2 + 1)
      /* ... on renvoie un indice de cette valeur */
      return k;
  }
  /* si on n'a pas trouvé de valeur dominante en "fouillant" la moitié "gauche", */
  /* on fait la même recherche avec la moitié "droite" */
  k = dominant_tab_rec(t, m+1, fin);
  if (k > m)
  {
    cpt = 0;
    for(i = deb; i <= fin; ++i)
    {
      if (t[i] == t[k])
        ++cpt;
    }
    if (cpt >= n/2 + 1)
      return k;
  }
  return -1;
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
int saisie_entier (int vmin, int vmax) {
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
			do {scanf("%c", &c);}
			while (c != ' ' && c != '\t' && c != '\n');
    }
    printf("Erreur ! Recommencez !");
  }
  while (1);
}
