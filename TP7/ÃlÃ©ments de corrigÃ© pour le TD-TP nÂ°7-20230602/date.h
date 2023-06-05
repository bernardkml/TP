#ifndef DATE_H /* garde d'inclusion */
#define DATE_H

struct date {
	unsigned jour;
	unsigned mois;
	unsigned annee;
};

/** Fonction qui alloue de l'espace sur le tas pour une struct date */
/* et renvoie l'adresse du bloc alloué */
struct date * allouer_date(void);

/** Fonction qui affiche les valeurs des champs de la date passée en argument */
void afficher_date(const struct date *);

/** Fonction qui renvoie -1 si d1 est antérieure à d2, */
/**          qui renvoie 1 si d1 est postérieure à d2, */
/**          qui renvoie 0 si les dates d1 et d2 sont identiques */
int comparer_date(const struct date *d1, const struct date * d2);

/** Fonction qui libère tout l'espace occupé sur le tas par une date */
void detruire_date (struct date **);


#endif
