#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* pour la fonction clock, le type clock_t et CLOCKS_PER_SEC */

#define N 50

unsigned long long bin (unsigned long long, unsigned long long);
unsigned long long bin_mem (unsigned long long, unsigned long long);
unsigned long long bin_ter (unsigned long long, unsigned long long);
unsigned long long bin_it (unsigned long long, unsigned long long);
void usage_bin (char []);

/* Variables globales pour le décompte des appels (fonctions bin et bin_mem) */
/* ou des multiplications et divisions (fonction bin_iter) */
unsigned long long C_bin = 0, C_mem = 0, C_ter = 0, C_it = 0;

int main (int argc, char * argv[]) {
  unsigned long long n, p, res;
  clock_t t_deb, t_fin;
  double t_exec;

  if (argc != 3) {
    printf ("Erreur dans le nombre d'arguments !\n");
    usage_bin (argv[0]);
    return EXIT_FAILURE;
  }

  n = strtoul (argv[1], NULL, 10);
  p = strtoul (argv[2], NULL, 10);

  /* Itératif */
  t_deb = clock();
  res = bin_it (n, p);
  t_fin = clock();
  t_exec = (double)(t_fin - t_deb)/CLOCKS_PER_SEC; /* en secondes */
  printf ("binomial (%llu, %llu) = %llu [nbre de mult. et div. = %llu] (itératif)\n", n, p, res, C_it);
  printf("Durée d'exécution (itératif) = %lf s \n", t_exec);
  /* Récursif avec mémoïsation */
  t_deb = clock();
  res = bin_mem (n, p);
  t_fin = clock();
  t_exec = (double)(t_fin - t_deb)/CLOCKS_PER_SEC; /* en secondes */
  printf ("binomial (%llu, %llu) = %llu [nbre d'appels = %llu] (récursif avec mémoïsation)\n", n, p, res, C_mem);
  printf("Durée d'exécution (avec mémoïsation) = %lf s \n", t_exec);
  /* Récursif terminal */
  t_deb = clock();
  res = bin_ter (n, p);
  t_fin = clock();
  t_exec = (double)(t_fin - t_deb)/CLOCKS_PER_SEC; /* en secondes */
  printf ("binomial (%llu, %llu) = %llu [nbre d'appels = %llu] (récursif terminal)\n", n, p, res, C_ter);
  printf("Durée d'exécution (récursif terminal) = %lf s \n", t_exec);
  /* Récursif naïf */
  t_deb = clock();
  res = bin (n, p);
  t_fin = clock();
  t_exec = (double)(t_fin - t_deb)/CLOCKS_PER_SEC; /* en secondes */
  printf ("binomial (%llu, %llu) = %llu [nbre d'appels = %llu = %llu] (récursif naïf)\n", n, p, res, C_bin, 2*res - 1);
  printf("Durée d'exécution (récursif naïf) = %lf s \n", t_exec);

  return EXIT_SUCCESS;
}

/** Fonction qui renvoie le coefficient binomial(n,p) en implémentant "naïvement" */
/* le schéma de récursion */
/*     binomial(n,p) = { 0 si n>p */
/*                     { 1 si p=0 ou p=n */
/*                     { binomial(n-1,p) + binomial(n-1,p-1) sinon */
/** Nbre total d'appels (initial et récursifs) */
/*     Cpt_bin(n,p) = { 1 si n > p ou p = 0 ou p = n */
/*                    { 1 + Cpt_bin(n-1,p) + Cpt_bin(n-1,p-1) sinon */
/*  i.e. Cpt_bin(n,p) = 2*binomial(n,p) -1 si 0 < p < n et Cpt_(2n,n) ~ 2*4^n / sqrt(\pi * n) */
/*  Par exemple, C_bin(10, 4) = 419 */
unsigned long long bin (unsigned long long n, unsigned long long p) {
  ++C_bin; /* compteur d'appels */
  if (n < p) return 0;
  if (p == 0 || p == n) return 1;
  return bin (n-1, p-1) + bin (n-1, p);
}

/** Fonction qui renvoie le coefficient binomial(n,p) en implémentant */
/* le même schéma de récursion avec une table d'association (mémoïsation) */
/*     binomial(n,p) = { 0 si n > p */
/*                     { 1 si p = 0 ou p = n*/
/*                     { binomial(n-1,p) + binomial(n-1,p-1) sinon */
/** Nombre total d'appels (initial et récursifs) */
/*     C_mem(n,p) = 1 + 2p(n-p) si 0 ≤ p ≤ n */
/*     Par exemple, C_mem(10, 4) = 49 */
unsigned long long bin_mem_2 (unsigned long long n, unsigned long long p, unsigned long long bin_tab[][N]) {
  ++C_mem; /* compteur d'appels */
  if (n < p) return 0;
  if (p == 0 || p == n) return (bin_tab[n][p] = 1);
  if (bin_tab[n][p] == 0)
    bin_tab[n][p] = bin_mem_2(n-1, p, bin_tab) + bin_mem_2(n-1, p-1, bin_tab);
  return bin_tab[n][p];
}
/** Appel initial */
unsigned long long bin_mem (unsigned long long n, unsigned long long p) {
  unsigned long long bin_tab[N][N] = {0};
  return bin_mem_2 (n, p, bin_tab);
}

/** Fonction récursive terminale qui renvoie le coefficient binomial(n,p) en implémentant */
/* le schéma de récursion ci-dessous */
/*     binomial(n,p) = { 0 si n > p */
/*                     { 1 si p = 0 ou p = n*/
/*                     { (n/p)binomial(n-1,p-1) sinon */
unsigned long long bin_ter_2 (unsigned long long n, unsigned long long p, unsigned long long x, unsigned long long y) {
  ++C_ter; /* compteur d'appels */
  if (n < p) {return 0;}
  if (p == 0 || p == n) {return y/x;}
  return bin_ter_2 (n-1, p-1, p*x, n*y);
}
/** Appel initial */
unsigned long long bin_ter (unsigned long long n, unsigned long long p) {
  return bin_ter_2 (n, p, 1, 1);
}
/** Fonction qui renvoie le coefficient binomial(n,p) en calculant n! / (p!(n-p)!) */
/** Nombre de multiplications et de divisions */
/*    C_iter(n,p) = { 2 * (min{p,n-p} - 1) + 1 si 0 < p < n */
/*                = { 0 sinon */
/*    Par exemple, C_iter(10,4) = 7 */
unsigned long long bin_it (unsigned long long n, unsigned long long p) {
  unsigned long long den = 1, num = n;
  unsigned long long i, q;
  q = p > n-p ? n-p : p;
  if (p > n) { return 0; }
  if (p == 0 || p == n) { return 1; }
  for (i = 2; i <= q ; i ++) {
    C_it += 2; /* compteur de multiplications */
    den *= i;
    num *= n - i + 1;
  }
  ++C_it; /* compteur de divisions */
  return num / den;
}

void usage_bin (char * s) {
  printf ("%s unsigned long long unsigned long long\n", s);
  printf("Argument 1 (unsigned long long int) : n \n");
  printf("Argument 2 (unsigned long long int) : p \n");
}
