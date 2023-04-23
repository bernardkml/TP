/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <time.h> /* pour le temps */

/* declaration constantes et types utilisateurs */

typedef struct polynome {
    int * coefficient; 
    int taille;
    int degre;
} polynome;

/* declaration de fonctions utilisateurs */

polynome * creer_polynome(unsigned int taille);
void afficher_polynome(const struct polynome *p);
polynome * scalaire_polynome(polynome * p,  int a);
void reformater_polynome(polynome * p);
polynome * additioner_polynome(const polynome *p, const struct polynome *q);
polynome * deriver_polynome(polynome *p);
polynome * multiplier_polynome(polynome * p, polynome * q);
void detruire_polynome(polynome **p);
/* fonction principale */
int main(int argc, char **argv)
{
    /* declaration et initialisation des variables */
    int dmin, dmax, λ;
    polynome *p, *q, *dp, *sp, *mp;
    /* ici faire quelque chose */
    srand(time(NULL));
    if (argc != 3)
    {
        printf("T'es bêtes ou quoi ???? 🤣🫵\n");
        return EXIT_FAILURE;
    }
    dmin = atoi(argv[1]);
    dmax = atoi(argv[2]);
    p = creer_polynome(dmax);
    q = creer_polynome(dmin);
    p->coefficient[0] = rand()%19-9;
	p->coefficient[1] = rand()%19-9;
	p->coefficient[2] = rand()%19-9;
	p->degre = rand()%8;
	q->coefficient[0] = rand()%19-9;
	q->coefficient[1] = rand()%19-9;
	q->coefficient[2] = rand()%19-9;
	q->degre = rand()%8;
    printf("Polynôme p : ");
    afficher_polynome(p);
    printf("\n");
	printf("Polynôme q : ");
	afficher_polynome(q);
    printf("\n");
    λ = rand()%8;
    sp = scalaire_polynome(p, λ);
	printf("multiplication de p par le scalaire λ = %d : ", λ);
	afficher_polynome(sp);
    printf("\n");
    mp = multiplier_polynome(p, q);
	printf("multiplication de p par q : ");
	afficher_polynome(mp);
    printf("\n");
    dp = deriver_polynome(p);
	printf("polynôme dérivé de p : ");
	afficher_polynome(dp);
    printf("\n");

    detruire_polynome(&p);
	detruire_polynome(&q);
	detruire_polynome(&sp);
	detruire_polynome(&mp);
	detruire_polynome(&dp);

    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
int minimum(int x, int y)
{
    if (x < y)
    {
        return x;
    } else {
        return y;
    }
    
}
int maximum(int x, int y)
{
    if (x > y)
    {
        return x;
    } else {
        return y;
    }
    
}

polynome * creer_polynome(unsigned int taille)
{
    polynome * res = malloc(sizeof(polynome));
    if (res == NULL)
    {
        perror("Echec d'allocution");
        exit(2);
    }
    res->taille = taille;
    res->degre = -1;
    res->coefficient = malloc(res->taille*sizeof(int));

    return res;
}
void afficher_polynome(const polynome *p)
{
	if (p == NULL) {
		printf("NULL");
		return;
	}
	if (p->degre < 0) {
		printf("0");
		return;
	}
	for (int i = p->degre; i >= 0; --i) {
		printf("%d", p->coefficient[i]);
		if (i > 0) {
			printf("X");
			if (i > 1)
				printf("^%d", i);
			printf(" + ");
		}
	}
	printf ("\n");
}

polynome * scalaire_polynome(polynome * p, int a)
{
    polynome * sp = creer_polynome(p->taille);
    if (sp == NULL)
    {
        perror("Echec d'allocution");
        exit(2);
    }
    sp->degre = p->degre;

    if (a != 0)
    {
        for (int  i = 0; i < sp->degre; ++i)
        {
            sp->coefficient[i] = p->coefficient[i]*a;
        } 
    } else {
        p->degre = -1;
        reformater_polynome(sp);
    } 
    return sp;
}



void reformater_polynome(polynome * p)
{
   int * nouv_coeff = NULL;
    if (p->taille > p->degre+1)
    {
        nouv_coeff = malloc(p->degre+1*sizeof(int));
    }
    p->taille = p->degre+1;
    for (int i = 0; i < p->degre; ++i)
    {
        nouv_coeff[i] = p->coefficient[i];
    }
    free(p->coefficient);
    p->coefficient = nouv_coeff; 
}



polynome * deriver_polynome(polynome *p)
{
    polynome* dp = creer_polynome(p->taille - 1);
	dp->degre = p->degre - 1;

	for (int i = 1; i < dp->taille; i++) {
		dp->coefficient[i-1] = p->coefficient[i]*i;
	}

	return dp;
}

polynome * multiplier_polynome(polynome * p, polynome * q)
{

	polynome* mp = creer_polynome(p->degre + q->degre + 1);
	mp->degre = p->degre + q->degre;
    if (mp == NULL)
    {
        perror("Echec d'allocution");
        exit(2);
    }

    for (int i = 0; i < mp->taille; i++) {
		mp->coefficient[i] = 0;
	}
	for (int i = 0; i < p->taille; i++)
    {
        for (int j = 0; j < q->taille; j++)
        {
            mp->coefficient[i] += p->coefficient[i] * q->coefficient[j];
        }
    }
	return mp;
}

void detruire_polynome(polynome **p)
{
    free((*p)->coefficient);
    free(*p);
    *p = NULL;
}