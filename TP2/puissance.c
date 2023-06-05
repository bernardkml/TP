#include <stdio.h>
#include <stdlib.h>

double puiss (double, unsigned);
double puiss_ter (double, unsigned);
double puiss_rap (double, unsigned);
double puiss_rap_ter (double, unsigned);
void usage_exponentielle(char []);

static unsigned Cpt = 0, Cpt_rap = 0, Cpt_ter = 0, Cpt_rap_ter = 0;

int main (int argc, char ** argv) {
  if (argc != 3) {
    printf ("Erreur sur le nombre d'arguments !\n");
    usage_exponentielle(argv[0]);
    return EXIT_FAILURE;
  }
  else {
    /* Initialisation de x avec la valeur (double) du 1er argument du programme */
    double x = strtod (argv[1], NULL);
    /* Initialisation de n avec la valeur (unsigned) du 2nd argument du programme */
    unsigned n = strtoul (argv[2], NULL, 10);

    /* Calcul (et affichage) de la valeur de x^n en appelant */
    /* quatre fonctions distinctes */
    printf ("Exponentiation récursive non terminale :\n");
    double res = puiss (x, n);
    printf ("%lf puissance %u = %lf (%u appels)\n", x, n, res, Cpt);
    printf ("Exponentiation récursive rapide non terminale :\n");
    res = puiss_rap (x, n);
    printf ("%lf puissance %u = %lf (%u appels)\n", x, n, res, Cpt_rap);
    printf ("Exponentiation récursive terminale :\n");
    res = puiss_ter (x, n);
    printf ( "%lf puissance %u = %lf (%u appels)\n", x, n, res, Cpt_ter);
    printf ("Exponentiation récursive rapide terminale :\n");
    res = puiss_rap_ter (x, n);
    printf ( "%lf puissance %u = %lf (%u appels)\n", x, n, res, Cpt_rap_ter);
    return EXIT_SUCCESS;
    }
}

double puiss (double x, unsigned n) {
  Cpt++;
  if (n == 0) return 1;
  return x * puiss (x, n-1);
}

double puiss_ter_2 (double x, unsigned n, double y) {
  Cpt_ter++;
  if (n == 0) return y;
  return puiss_ter_2 (x, n-1, x*y);
}

double puiss_ter (double x, unsigned n) {
  return puiss_ter_2 (x, n, 1);
}

double puiss_rap (double x, unsigned n) {
  Cpt_rap++;
  if (n == 0) return 1;
  if (n%2 == 0)
    return puiss_rap (x*x, n/2);
  else
    return x * puiss_rap (x*x, n/2);
}

double puiss_rap_ter_2 (double x, unsigned n, double y) {
  Cpt_rap_ter++;
  if (n == 0) return y;
  if (n%2 == 0)
    return puiss_rap_ter_2 (x*x, n/2, y);
  else
    return puiss_rap_ter_2 (x*x, n/2, x*y);
}

double puiss_rap_ter (double x, unsigned n) {
  return puiss_rap_ter_2 (x, n, 1);
}

/** Affichage de la syntaxe de la ligne de commande */
void usage_exponentielle(char cmd[]) {
	printf("Usage: %s double int\n", cmd);
  printf("Argument 1 (double) : base de l'exponentiation \n");
  printf("Argument 2 (int) : l'exposant\n");
}
