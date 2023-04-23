/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <time.h> /* pour le temps */

/* declaration constantes et types utilisateurs */
struct uef
{
    unsigned coefficient;
    float note;
};

struct releve_BF_N2_info
{
    unsigned long identifiant;
    struct uef algebre;
    struct uef programmation;
    struct uef logique;
};

typedef struct releve_BF_N2_info * lien;
/* declaration de fonctions utilisateurs */
void initialiser_tab_releves (lien *t, int taille);
float moyenne_BF(lien t);
void afficher_moyenne_tab_releves(lien *t, int taille);
void trier_moyenne_tab_releves(lien *t, int taille);
void swap(lien * etu1, lien * etu2);
int nombre_BF_valide_releves(lien *t, int taille);
int recherche_tab_releves(lien *t, int taille, float m_min, float m_max);
/* fonction principale */
int main()
{
    /* declaration et initialisation des variables */
    lien * t = malloc(sizeof(lien)*10);
    /* ici faire quelque chose */
    srand(time(NULL));
    initialiser_tab_releves (t,10);
    moyenne_BF(*t);
    printf("Moyennes de tous les relevées du tableau\n\n");
    afficher_moyenne_tab_releves(t,10);
    trier_moyenne_tab_releves(t,10);
    printf("\n");
    printf("Tableau Trié\n\n");
    afficher_moyenne_tab_releves(t,10);
    nombre_BF_valide_releves(t,10);
    printf("\n");
    printf("Etudiants ayant validé\n\n");
    afficher_moyenne_tab_releves(t,10);
    printf("\n");
    printf("On a l'etudiant %d\n",recherche_tab_releves(t,10,2,20));
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */

/* Initialise un tableau de relevés */
/* Les identifiants sont engendrés de façon pseudo-aléatoire */
/* en respectant une 1re inscription en 2021 ou 2022 */
/* Les notes d'UEF sont initialisées de façon pseudo-aléatoire */
/* à des valeurs comprises entre 6 et 20 (au demi-point près) */
void initialiser_tab_releves (lien *t, int taille) {
  int i;
  for (i = 0; i < taille; ++i) {
    /* réservation d'espace mémoire pour les relevés référencés dans le tableau */
    t[i] = malloc(sizeof(struct releve_BF_N2_info));
    /* initialisation pseudo-aléatoire des champs des relevés */
    t[i]->identifiant = (121 + rand()%2)*100000 + rand()%18000;
    /*  À COMPLÉTER */
    t[i]->algebre.coefficient = 7;
    t[i]->programmation.coefficient = 6;
    t[i]->logique.coefficient = 4;
    t[i]->algebre.note = rand()%20;
    t[i]->programmation.note = rand()%20;
    t[i]->logique.note = rand()%20;
  }
}

float moyenne_BF(lien t)
{

  unsigned moyennes = ((t->algebre.note)*(t->algebre.coefficient))+((t->programmation.note)*(t->programmation.coefficient))+((t->logique.note)*(t->logique.coefficient))/(t->logique.coefficient)+(t->programmation.coefficient)+(t->algebre.coefficient);
  return moyennes;
}

void afficher_moyenne_tab_releves(lien *t, int taille)
{
  for (int i = 0; i < taille; ++i)
  {
    printf("moyenne BF de l'étudiant(e) %ld = %g\n", t[i]->identifiant, moyenne_BF(*(t+i)));
  }  
}

void trier_moyenne_tab_releves(lien *t, int taille)
{
  int j;
  for (int i = 1; i < taille; ++i)
  {
    j = i;
    while (j > 0 && moyenne_BF(t[j]) < moyenne_BF(t[j-1]))
    {
      swap(t+j, t+j-1);
      --j;
    }
  }
}

void swap(lien * etu1, lien * etu2)
{
  lien tmp = *etu1;
  *etu1 = *etu2;
  *etu2 = tmp;
}

int nombre_BF_valide_releves(lien *t, int taille)
{
  int i = 0;
  while (moyenne_BF(t[i]) < 10)
  {
    ++i;
    --taille;
  }
  return taille;
}

int recherche_tab_releves(lien *t, int taille, float m_min, float m_max)
{
    int m = taille/2;
     if (taille <= 0) {
    return -1;
  }
  if (moyenne_BF(t[m]) > m_max) {
        return recherche_tab_releves(t,m,m_min,m_max);
  } else {    
     int res = recherche_tab_releves(t,taille - (m-1), m_min,m_max);
     return res;
    }
}