#ifndef TURING_H /* garde d'inclusion */
#define TURING_H

#include "individu.h"

struct laureat_Turing 
{
    struct individu *laureat;
    unsigned annee_prix;
};


/** Fonction qui alloue de l'espace sur le tas pour une chaîne de n caractères */
/** et renvoie l'adresse du bloc, de taille n+1, alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
char * allouer_chaine (int n);

/** Fonction qui alloue de l'espace sur le tas pour un lauréat */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR allouer_tab_laureat */
struct laureat_Turing * allouer_laureat (void);

/** Fonction qui alloue l'espace mémoire sur le tas */
/* pour un tableau de n adresses de lauréats */
/* (et pour n structures laureat_Turing) */
/* et renvoie l'adresse du bloc alloué */
/** N.B. CETTE FONCTION EST APPELÉE PAR init_tab */
struct laureat_Turing ** allouer_tab_laureat (int n);

/** Fonction qui libère tout l'espace mémoire occupé sur le tas */
/* par le lauréat Turing pointé par lt */
void detruire_laureat (struct laureat_Turing ** lt);

/** Fonction qui affiche le titre, le prénom et le nom du laureat, (la date et la ville de création) de l'ltéra lt */
void afficher_laureat(struct laureat_Turing ** lt);


#endif

