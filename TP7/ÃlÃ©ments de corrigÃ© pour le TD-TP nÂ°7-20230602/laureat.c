#include "laureat.h"
#include "date.h" /* Cette inclusion n'est pas nécessaire */
#include "individu.h" /* Cette inclusion n'est pas nécessaire */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Fonction qui alloue de l'espace sur le tas pour un lauréat */
/* et renvoie l'adresse du bloc alloué */
struct laureat_Turing * allouer_laureat (void) {
		struct laureat_Turing * lt = malloc(sizeof(struct laureat_Turing));
		if (lt == NULL) {
			perror("Échec allocation lauréat");
			exit(EXIT_FAILURE);
		}
		return lt;
}

/** Fonction qui alloue l'espace mémoire sur le tas */
/* pour un tableau de n adresses de lauréats */
/* (et pour n structures laureat_Turing) */
/* et renvoie l'adresse du bloc alloué */
struct laureat_Turing ** allouer_tab_laureat (int n) {
	int i;
	struct laureat_Turing ** t = malloc (sizeof(struct laureat_Turing *) * n);
	if (t == NULL) {
		perror("Échec allocation tableau");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; ++i)
		t[i] = allouer_laureat();
	return t;
}

/** Fonction qui libère tout l'espace mémoire occupé sur le tas */
/* par le lauréat Turing pointé par lt */
void detruire_laureat (struct laureat_Turing ** lt) {
	detruire_individu(&(*lt)->laureat);
	free(*lt);
  *lt = NULL;
}

/** Fonction qui libère tout l'espace mémoire occupé sur le tas */
/* par le tableau de lauréats Turing tab, de taille taille, */
void detruire_tab_laureat (struct laureat_Turing *tab[], int taille) {
	int i;
	for (i = 0; i < taille; i ++) {
		detruire_laureat (tab+i);
	}
	free(tab);
}

/** Fonction qui affiche le titre, le prénom et le nom du laureat, (la date et la ville de création) de l'ltéra lt */
void afficher_laureat (const struct laureat_Turing * lt) {
	afficher_individu(lt->laureat);
	printf(" [lauréat %u]", lt->annee_prix);
}

/** Fonction qui affiche le contenu du tableau de  tab, de taille taille, */
void afficher_tab_laureat (struct laureat_Turing *tab[], int taille) {
	int i;
	for (i = 0; i < taille; i ++) {
		afficher_laureat(tab[i]);
		printf("\n");
	}
}

/** Fonction qui échange les adresses de lauréats pointées par les deux arguments */
void echanger_laureat (struct laureat_Turing **lt1, struct laureat_Turing **lt2) {
	struct laureat_Turing *tmp = *lt1;
	*lt1 = *lt2;
	*lt2 = tmp;
}
