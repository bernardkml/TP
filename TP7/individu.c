/* Fichier individu.c */
#include "individu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Fonction qui alloue l'espace mémoire sur le tas pour un individu */
/* qu'elle initialise champ par champ avec les paramètres d'entrée */
/** et renvoie l'adresse du bloc alloué pour l'individu */
struct individu * allouer_init_individu (const char *prenom, const char *nom, const struct date *d_naissance, const char *origine)
{
    struct individu * res = malloc(sizeof(struct individu));
    if (res == NULL)
    {
        perror("l'alloc a pas marcher frrr\n");
        exit(EXIT_FAILURE);
    }
    res->prenom = malloc(sizeof(char));
    strcpy(res->prenom, prenom);
    res->nom = malloc(sizeof(char));
    strcpy(res->nom,nom);
    res->naissance = allouer_init_date(d_naissance->jour,d_naissance->mois,d_naissance->annee);
    res->origine = malloc(sizeof(char));
    strcpy(res->origine,origine);
    return res;
}

/** Fonction qui calcule le nombre d'années révolues */
/* de l'individu ind à la date d */
/** Par exemple, un individu né le 7 avril 1950 */
/* a 49 années révolues le 7 avril 2000 et en a 50 le 8 avril 2000 */
int nbre_annees_revolues (const struct individu * ind, const struct date * d) 
{
	struct date * d_copie = allouer_init_date(ind->naissance->jour, ind->naissance->mois, ind->naissance->annee);
	int res = d->annee - (d_copie->annee + 1);
	d_copie->annee += res + 1;
	if (comparer_date(d_copie, d) < 0)
		res ++;
	detruire_date(&d_copie);
	return res;
}


/** Fonction qui libère toute la mémoire occupée sur le tas */
/* par l'individu dont l'adresse est pointée par ind */
void detruire_individu (struct individu ** ind)
{
	free((*(ind))->prenom);
    free((*(ind))->nom);
    free((*(ind))->origine);
    free((*(ind)));
	*ind = NULL;
}

/** Fonction qui affiche le prénom, le nom, */
/* la date et le pays de naissance de l'individu pointé par ind */
void afficher_individu (const struct individu * ind)
{
    printf("Prénom du lauréat : %s\t", ind->prenom);
    printf("Nom du lauréat: %s\t", ind->nom);
    afficher_date(ind->naissance);
    printf("Origine du lauréat: %s\t", ind->origine);
}

