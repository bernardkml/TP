#ifndef _LAUREAT_H
#define _LAUREAT_H

struct laureat_Turing {
  struct individu *laureat; /* laureat du prix Turing */
  unsigned annee_prix; /* annee de la recompense */
};

struct laureat_Turing ** allouer_tab_laureat (int);
void detruire_laureat (struct laureat_Turing **);
void afficher_laureat (const struct laureat_Turing *);
void afficher_tab_laureat (struct laureat_Turing **, int);
void detruire_tab_laureat (struct laureat_Turing **, int);
void echanger_laureat (struct laureat_Turing **, struct laureat_Turing **);

#endif
