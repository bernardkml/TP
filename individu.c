#include "date.h" /* Cette inclusion n'est pas nécessaire */
#include "individu.h"
#include <string.h> /* pour strcpy */
#include <stdlib.h> /* pour malloc, free, sizeof */
#include <stdio.h> /* pour printf */

/* Fonction qui alloue l'espace mémoire sur tas pour un individu */
/** et renvoie l'adresse du bloc alloué pour l'individu */
struct individu * allouer_individu (void) {
	struct individu * ind = malloc(sizeof(struct individu));
	if (ind == NULL) {
		perror("Échec allocation individu");
		exit(EXIT_FAILURE);
	}
	return ind;
}

/** Fonction qui libère toute la mémoire occupée par l'individu pointé par ind */
void detruire_individu (struct individu ** ind) {
	free((*ind)->nom);
	free((*ind)->prenom);
	detruire_date(&(*ind)->naissance);
	free((*ind)->origine);
	free(*ind);
	*ind = NULL;
}

/** Fonction qui affiche le prénom, le nom, la date et le pays de naissance de l'individu pointé par ind */
void afficher_individu (const struct individu * ind) {
	printf("%s %s né le ", ind->prenom, ind->nom);
	afficher_date(ind->naissance);
	printf(" à %s", ind->origine);
}

/** Fonction qui calcule le nombre d'années révolues */
/* de l'individu pointé par ind à la date pointée par d */
/** Par exemple, un individu né le 7 avril 1950 */
/* a 49 années révolues le 7 avril 2000 et en a 50 le 8 avril 2000 */
/** Complexité : \Theta(1) */
int nbre_annees_revolues (const struct individu * ind, const struct date * d) {
	struct date d_copie = *(ind->naissance);
	int res = d->annee - d_copie.annee - 1;
	d_copie.annee = ind->naissance->annee;
	if (comparer_date(&d_copie, d) < 0)
		++res;
	return res;
}
