#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

struct uef {
  unsigned coefficient;
  float note;
};

struct releve_BF_N2_info {
  unsigned long identifiant;
  struct uef algebre;
  struct uef programmation;
  struct uef logique;
};
typedef struct releve_BF_N2_info * lien;

float moyenne_BF (lien);
/* void initialiser_tab_releves(lien *, int); */ /* (ancienne version) */
lien * initialiser_tab_releves(int);
void afficher_moyenne_tab_releves(lien *, int);
void trier_moyenne_tab_releves(lien *, int);
int nombre_BF_valide_tab_releves(lien *, int);
int rechercher_tab_releves(lien *, int, float, float);

int main() {
  lien * t_releves;
  int pos_moy;

  /* Initialisation du tableau de releves */
  srand(time(NULL));
  /* initialiser_tab_releves(t_releves, N); */ /* (ancienne version)*/
  t_releves = initialiser_tab_releves(N);

  /* Calcul et affichage des moyennes */
  printf("Affichage des moyennes du tableau de relevés \n");
  afficher_moyenne_tab_releves(t_releves, N);

  /* Tri selon la moyenne et réaffichage */
  trier_moyenne_tab_releves(t_releves, N);
  printf("Affichage (après tri) des moyennes du tableau de relevés \n");
  afficher_moyenne_tab_releves(t_releves, N);

  /* Calcul et affichage du nombre d'étudiant(e)s ayant la moyenne dans le BF */
  printf("Il y a %d étudiant(e) ayant la moyenne dans le BF \n", nombre_BF_valide_tab_releves(t_releves, N));

  /* Affichage des résultats de la recherche */
  pos_moy = rechercher_tab_releves(t_releves, N, 12.0, 14.0);
  if (pos_moy == -1)
    printf("Aucun(e) étudiant(e) n'a de moyenne BF entre %4.2f et %4.2f \n", 12.0, 14.0);
  else
    printf("L'étudiant(e) n° %lu a une moyenne BF égale à %4.2f \n", t_releves[pos_moy]->identifiant, moyenne_BF(t_releves[pos_moy]));

  return EXIT_SUCCESS;
}

float moyenne_BF(lien etu) {
  unsigned somme_coeff = etu->algebre.coefficient + etu->programmation.coefficient + etu->logique.coefficient;
  return (etu->algebre.coefficient * etu->algebre.note +
    etu->programmation.coefficient * etu->programmation.note +
    etu->logique.coefficient * etu->logique.note)/somme_coeff;
}

/* Initialise un tableau de relevés */
/* Les identifiants sont engendrés de façon pseudo-aléatoire */
/* en respectant une 1re inscription en 2021 ou 2022 */
/* Les notes d'UEF sont initialisées de façon pseudo-aléatoire */
/* à des valeurs comprises entre 6 et 20 (au demi-point près) */
/* (ancienne version)
void initialiser_tab_releves (lien *t, int taille) {
  int i;
  for (i = 0; i < taille; ++i) {
    t[i] = malloc(sizeof(struct releve_BF_N2_info));
    t[i]->identifiant = (121 + rand()%2)*100000 + rand()%18000;
    t[i]->algebre.coefficient = 7;
    t[i]->algebre.note = 6.0 + (rand()%28)*0.5;
    t[i]->programmation.coefficient = 6;
    t[i]->programmation.note = 6.0 + (rand()%28)*0.5;
    t[i]->logique.coefficient = 4;
    t[i]->logique.note = 6.0 + (rand()%28)*0.5;
  }
} */
lien * initialiser_tab_releves (int taille) {
  int i;
  lien * t = malloc(taille * sizeof(lien));
  if (t == NULL) {
    perror("Erreur allocation tableau");
    exit(2);
  }
    for (i = 0; i < taille; ++i) {
    t[i] = malloc(sizeof(struct releve_BF_N2_info));
    if (t[i] == NULL) {
      fprintf(stderr, "Erreur allocation t[%d] \n", i);
      exit(3);
    }
    t[i]->identifiant = (121 + rand()%2)*100000 + rand()%18000;
    t[i]->algebre.coefficient = 7;
    t[i]->algebre.note = 4.0 + (rand()%29)*0.5;
    t[i]->programmation.coefficient = 6;
    t[i]->programmation.note = 4.0 + (rand()%29)*0.5;
    t[i]->logique.coefficient = 4;
    t[i]->logique.note = 4.0 + (rand()%29)*0.5;
  }
  return t;
}

/* Affiche toutes les moyennes de BF des relevés du tableau t */
void afficher_moyenne_tab_releves (lien *t, int taille) {
  int i;
  for (i = 0; i < taille; ++i) {
    printf("moyenne BF de l'étudiant(e) n°%lu = %4.2f \n", t[i]->identifiant, moyenne_BF(t[i]));
  }
}

/* Rendu inutile par l'optimisation du tri ci-dessous */
/* void echanger_lien (lien * etu_1, lien * etu_2) {
  lien tmp = *etu_1;
  *etu_1 = *etu_2;
  *etu_2 = tmp;
}
*/

/** Implémente un tri "optimisé" par insertion pour réordonner les liens du tableau de relevés t */
/* dans l'ordre croissant des moyennes de BF des relevés référencés par ces liens, */
/* (L'adresse de) t est reçu(e) comme comme premier paramètre d'entrée */
/* la taille de t est reçue comme deuxième paramètre d'entrée */
/** Dans le cas le plus défavorable, le nombre total de comparaisons de moyennes est : */
/* 1 + 2 + ... + (taille-2) + (taille-1) = taille(taille-1)/2 */
/** Dans le cas le plus favorable, le nombre total de comparaisons de moyennes est : */
/* 1 + 1 + ... + 1 + 1 (taille-1 termes) = taille-1 */
void trier_moyenne_tab_releves (lien *t, int taille) {
  int i, j;
  float m;
  lien etu;
  /* après l'itération i de la boucle suivante, */
  /* les valeurs occupant les cases d'indice 0 à i sont rangées dans l'ordre croissant */
  for (i = 1; i < taille; ++i) {
    j = i;
    m = moyenne_BF(t[j]);
    etu = t[i];
    while (j > 0 && m < moyenne_BF(t[j-1])) {
      t[j] = t[j-1];
      --j;
    }
    t[j] = etu;
  }
}

/* Renvoie le nombre d'étudiants ayant validé le BF dans le tableau de relevés t */
/** Le tableau t EST SUPPOSÉ TRIÉ SELON L'ORDRE CROISSANT DES MOYENNES DE BF */
/* (L'adresse de) t est reçu(e) comme comme premier paramètre d'entrée */
/* la taille de t est reçue comme deuxième paramètre d'entrée */
int nombre_BF_valide_tab_releves(lien *t, int taille) {
    int i = 0, n = taille;
    while (i < taille && moyenne_BF(t[i]) < 10.0) { --n; ++i; }
    return n;
}

/** Implémente une recherche dichotomique dans un tableau de relevés t */
/** Le tableau t EST SUPPOSÉ TRIÉ SELON L'ORDRE CROISSANT DES MOYENNES DE BF */
/* (L'adresse de) t est reçu(e) comme comme premier paramètre d'entrée */
/* la taille de t est reçue comme deuxième paramètre d'entrée */
/* S'il existe dans t un lien vers un relevé de moyenne comprise entre m_min et m_max, */
/* renvoie l'indice d'un tel lien */
/* Sinon, renvoie -1 */
int rechercher_tab_releves(lien *t, int taille, float m_min, float m_max) {
  float moyenne;
  int milieu = taille/2;
  if (taille <= 0) return -1;
  moyenne = moyenne_BF(t[milieu]);
  if (moyenne >= m_min && moyenne <= m_max) return milieu;
  if (moyenne > m_max)
    return rechercher_tab_releves(t, milieu, m_min, m_max);
  else /* moyenne < m_min */ {
    int res = rechercher_tab_releves(t + milieu + 1, taille - (milieu + 1), m_min, m_max);
    /* si l'appel récursif renvoie -1, l'appel courant aussi -1 /*
    /* sinon, on ajoute m+1 à l'indice renvoyé par l'appel récursif pour tenir compte du décalage */
    return res < 0 ? -1 : milieu + 1 + res;
  }
}
