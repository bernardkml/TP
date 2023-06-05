#ifndef _OPERA_H
#define _OPERA_H

#include "date.h"
#include "individu.h"

struct opera {
	char * titre; /* le titre de l'opéra */
	struct date * date_creation; /* l'année de la création (i.e. de la première représentation) */
	char * ville_creation; /* ville de la création (i.e. de la première représentation) */
	struct individu * compositeur; /* nom du compositeur */
};

/** Fonction qui alloue de l'espace sur le tas pour un opéra */
/* et renvoie l'adresse du bloc alloué */
struct opera * allouer_opera (void);

/** Fonction qui libère toute la mémoire occupée par l'opéra pointé par op */
void detruire_opera (struct opera ** op);

/** Fonction qui crée et renvoie l'adresse d'un tableau d'opéras de taille taille */
struct opera ** allouer_tab_opera (int taille);

/** Fonction qui libère tout l'espace mémoire occupé sur le tas par le tableau d'opéras tab, de taille taille, */
void detruire_tab_opera (struct opera **tab[], int taille);

/** Fonction qui affiche le titre, le prénom et le nom du compositeur, (la date et la ville de création) de l'opéra op */
void afficher_opera (const struct opera * op);

/** Fonction qui affiche tous les opéras du tableau d'opéras tab, de taille taille, */
void afficher_tab_opera (struct opera *tab[], int taille);

/** Fonction qui affiche les opéras, référencés dans le tableau t, de taille n, */
/* qui ont été créés dans la ville de naissance de leur compositeur */
void select_tab_ville_creation (struct opera **t, int n);

/** Fonction qui supprime du tableau tab */
/*  tous les opéras dont le compositeur avait a années révolues lors de la création */
/* et renvoie l'adresse du nouveau tableau */
/* N.B. La taille du tableau est mise à jour */
/** Complexité : \Theta(N) si N est la taille du tableau */
struct opera **supprimer_tab_age_compositeur (struct opera **tab, int *taille, int a);

/** Fonction qui échange les adresses d'opéra pointées par les deux arguments */
void echanger_opera (struct opera **op1, struct opera **op2);

/** Fonction qui trie le tableau d'opéras tab, de taille n, */
/* selon l'ordre chronologique de création (tri à bulles) */
/** Complexité : \Theta(N^2) si N est la taille du tableau */
void trier_tab_date_creation (struct opera **tab, int n);

/** Fonction qui recherche dans le tableau d'opéras tab, de taille taille, */
/* SUPPOSÉ TRIÉ DANS L'ORDRE CHRONOLOGIQUE DES CRÉATIONS, un opéra créé au cours de l'année an */
/** Cette fonction affiche un tel opéra s'il s'en trouve un dans le tableau */
/* et affiche un message d'absence sinon */
/** Complexité : \Theta(\log_2 N) si N est la taille du tableau */
void recherche_tab_annee_creation (struct opera **tab, int taille, unsigned an);

/** Fonction qui initiale un tableau d'opéras avec les opéras */
/* stockés dans le fichier de nom n_fich */
/* et renvoie l'adresse ainsi initialisé */
/* (l'entier pointé par le 2e paramètre d'entrée */
/* prend la valeur du nombre d'opéras référencés dans le tableau initialisé) */
struct opera ** initialiser_tab_opera_fichier (char *n_fich, int * taille);

/** Fonction qui sauvegarde un tableau d'opéras t de taille n */
/* dans le fichier de nom n_fich */
void sauvegarder_tab_opera_fichier (struct opera **t, int n, char *n_fich);


#endif
