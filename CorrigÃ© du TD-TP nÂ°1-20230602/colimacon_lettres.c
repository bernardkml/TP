/* Ce programme lit une largeur (une valeur entière comprise entre 0 et 10) */
/* entrée au clavier par l'utilisateur puis affiche le colimaçon de cette largeur */
#include <stdlib.h>
#include <stdio.h>

#define N 10

void escargot_chaine(int, char[]);
int saisie_entier (int, int);
char lettre_suivante (char);

int main ()
{
	int cote;
	/* 111 = 11 x 10 + 1 caractères nécessaires */
	/* pour stocker le colimaçon de largeur 10 */
	char s[111];

	printf ("Tapez la valeur du côté : \n");
  cote = saisie_entier(0, N);

	/* stockage du colimaçon dans la chaîne s ...*/
	escargot_chaine(cote,s);
	/* ... et affichage de s */
	puts(s); /* ou printf("%s\n", s); */

	return EXIT_SUCCESS;
}

/** Renvoie le "successeur" de la lettre reçue comme paramètre d'entrée */
/* (on alterne les alphabets latins minuscule et majuscule */
char lettre_suivante (char c) {
	if ('z' == c) return 'A';
	if ('Z' == c) return 'a';
	return c + 1;
}

/** Stocke le colimaçon de largeur n dans la chaîne s */
void escargot_chaine(int n, char s[])
{
	int i = 0;
	char c = 'a';
	/* remplissage de la chaîne par des espaces */
	while (i < n*(n+1))
	{
		s[i] = ' ';
		i = i + 1;
	}
	/* placement du caractère de fin de chaîne */
	s[i] = '\0';
	/* placement des retours à la ligne */
	i = i - 1;
	while (i >= 0)
	{
		s[i] = '\n';
		i = i - (n+1);
	}
	/* remplacement des espaces par les lettres de l'escargot */
	i = 0;
	while (' ' == s[i])
	{
		/* remplissage horizontal gauche -> droite */
		while (' ' == s[i])
		{
			s[i] = c;
			c = lettre_suivante(c);
			i = i + 1;
		}
		i = i - 1 + (n+1);
		/* remplissage vertical haut -> bas */
		while ((i < n*(n+1))  && ' ' == s[i])
		{
			s[i] = c;
			c = lettre_suivante(c);
			i = i + (n+1);
		}
		i = i - (n+1) - 1;
		/* remplissage horizontal droite -> gauche */
		while (' ' == s[i])
		{
			s[i] = c;
			c = lettre_suivante(c);
			i = i - 1;
		}
		i = i + 1 - (n+1);
		/* remplissage vertical bas -> haut */
		while (i >= 0 && ' ' == s[i])
		{
			s[i] = c;
			c = lettre_suivante(c);
			i = i - (n+1);
		}
		i = i + (n+1) + 1;
	}
}

/* Lit une valeur entière entrée au clavier par l'utilisateur */
/* et renvoie cette valeur si elle est comprise entre vmin et vmax */
/* (Dans le cas contraire, demande à l'utilisateur de recommencer) */
int saisie_item (int vmin, int vmax) {
  int res, n;
  char c;
  do
  {
    printf("Tapez une valeur entière comprise entre %d et %d : ", vmin, vmax);
    n = scanf("%d", &res);
    if (1 == n && res >= 0 && res <= vmax)
      return res;
    /* si la lecture d'une valeur entière a échoué... */
    if (0 == n)
    {
      /* ...on "avale" la fin de la chaîne entrée au clavier par l'utilisateur */
      /* avant de lui demander de recommencer */
			do
      {
				scanf("%c", &c);
			}
			while (c != ' ' && c != '\t' && c != '\n');
		}
    printf("Erreur ! Recommencez !");
  }
  while (1);
}
