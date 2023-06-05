#include "opera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENTREE argv[1] /* Nom du fichier pour initialiser le tableau d'adresses d'opéras */
#define SORTIE argv[2] /* Nom du fichier pour sauvegarder le tableau d'adresses d'opéras après modifications */

void usage_opera (char *);

int main(int argc, char **argv) {
  int taille = 0;
  struct opera **tab_operas = NULL;

  if (argc != 3) {
    printf("Erreur sur le nombre d'arguments ! Recommencez.\n");
    usage_opera(argv[0]);
    return EXIT_FAILURE;
  }

  /* Initialisation de tab_operas */
  tab_operas = initialiser_tab_opera_fichier (ENTREE, &taille);

  /* Affichage du tableau */
  printf("\nLes %d opéras du tableau :\n", taille);
  afficher_tab_opera(tab_operas, taille);
  /* Affichage des opéras créés dans la ville de naissance de leur compositeur */
  printf("\nLes opéras du tableau créés dans la ville de naissance de leur compositeur sont :\n");
  select_tab_ville_creation(tab_operas, taille);
  /* Affichage du tableau trié selon l'ordre chronologique des créations */
  printf("\nLes opéras du tableau triés selon l'ordre chronologique des créations :\n");
  trier_tab_date_creation(tab_operas, taille);
  afficher_tab_opera(tab_operas, taille);
  /* Affichage d'un opéra créé en 1831 */
  printf("\nUn opéra du tableau créé en 1831 ?\n");
  recherche_tab_annee_creation(tab_operas, taille, 1831);
  /* Affichage d'un opéra créé en 1900 */
  printf("\nUn opéra du tableau créé en 1900 ?\n");
  recherche_tab_annee_creation(tab_operas, taille, 1900);
	/* Suppression des références aux opéras dont le compositeur avait 40 ans révolus lors de la création */
	/* et affichage du nouveau tableau */
  printf("\nTableau après suppression des opéras créés alors que leur compositeur avait 40 ans révolus :\n");
	tab_operas = supprimer_tab_age_compositeur(tab_operas, &taille, 40);
	afficher_tab_opera(tab_operas, taille);
	/* Sauvegarde du dernier état de tab_operas dans le fichier SORTIE */
	sauvegarder_tab_opera_fichier(tab_operas, taille, SORTIE);

  /* Nettoyage mémoire */
  detruire_tab_opera(&tab_operas, taille);
  /* tab_operas = NULL; */
  printf("Mémoire libérée...\n");

  return EXIT_SUCCESS;
}


void usage_opera (char * s) {
  printf("%s string string \n", s);
  printf("[Argument 1 (string) : nom du fichier utilisé pour l'initialisation du tableau]\n");
	printf("[Argument 2 (string) : nom du fichier utilisé pour la sauvegarde du tableau]\n");
}
