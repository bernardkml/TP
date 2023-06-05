#include "date.h"
#include <stdio.h> /* pour printf, perror */
#include <stdlib.h> /* pour EXIT_FAILURE, exit, malloc, free */
#include <time.h> /* pour time_t, struct tm, time et localtime */

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* et renvoie l'adresse du bloc alloué */
struct date * allouer_date(void) {
	struct date * res = malloc(sizeof(struct date));
	if (res == NULL) {
		perror("Échec allocation date");
		exit(EXIT_FAILURE);
	}
	return res;
}

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date * d) {
	printf("%u/%u/%u", d->jour, d->mois, d->annee);
}

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date * d1, const struct date * d2) {
	if(d1->annee < d2->annee)
		return -1;
	if (d1->annee > d2->annee)
		return 1;
	if (d1->mois < d2->mois)
		return -1;
	if (d1->mois > d2->mois)
		return 1;
	if (d1->jour < d2->jour)
		return -1;
	if (d1->jour > d2->jour)
		return 1;
	return 0;
}

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date ** d) {
	free(*d);
	*d = NULL;
}
