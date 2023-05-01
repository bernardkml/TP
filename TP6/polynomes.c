/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */
#include <time.h> /* pour le temps */

/* declaration constantes et types utilisateurs */

struct polynome {
    int * coefficient; 
    int taille;
    int degre;
};

/* declaration de fonctions utilisateurs */

struct polynome * creer_polynome(unsigned int taille);
struct polynome * alea_init_polynome(unsigned int d);
void afficher_polynome(struct polynome *p);
struct polynome * scalaire_polynome(struct polynome * p,  int a);
void reformater_polynome(struct polynome * p);
struct polynome * additioner_polynome(const struct polynome *p, const struct polynome *q);
struct polynome * deriver_polynome(struct polynome *p);
struct polynome * multiplier_polynome(struct polynome * p,struct polynome * q);
void detruire(struct polynome **p);
/* fonction principale */
int main(int argc, char **argv)
{
    /* declaration et initialisation des variables */
    int dmin, dmax;
    struct polynome *p, *q;
    /* ici faire quelque chose */
    srand(time(NULL));
    
    if ((argc != 3) || (argv[2] <= argv[1]))
        {
            printf("T'es bêtes ou quoi ???? 🤣🫵\nrentre 2 nombres nan !\n");
            return EXIT_FAILURE;
        }

    dmin = atoi(argv[1]);
    dmax = atoi(argv[2]);
    p = alea_init_polynome(dmax);
    q = alea_init_polynome(dmin);
    printf("Polynôme p : ");
    afficher_polynome(p);
    printf("\n");
	printf("Polynôme q : ");
	afficher_polynome(q);
    printf("\n");
    printf("Polynôme q affichant le produit de p et q : ");
    q = multiplier_polynome(p,q);
    afficher_polynome(q);
    printf("\n");
    printf("\n");

    detruire(&p);
	detruire(&q);

    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
struct polynome * alea_init_polynome(unsigned int d)
{
    srand(time(NULL));
    struct polynome * test = creer_polynome(d);
    test->degre = d;
    for (int i = 0; i < test->degre; ++i)
    {
        test->coefficient[i] = rand()%18;
    } 

    return test;   
}
struct polynome * creer_polynome(unsigned int taille)
{
    struct polynome * res = malloc(sizeof(struct polynome));
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
void afficher_polynome(struct polynome * p)
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

struct polynome * scalaire_polynome(struct polynome * p, int a)
{
    struct polynome * sp = creer_polynome(p->taille);
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



void reformater_polynome(struct polynome * p)
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



struct polynome * deriver_polynome(struct polynome *p)
{
    struct polynome* dp = creer_polynome(p->taille - 1);
	dp->degre = p->degre - 1;

	for (int i = 1; i < dp->taille; i++) {
		dp->coefficient[i-1] = p->coefficient[i]*i;
	}

	return dp;
}

struct polynome * multiplier_polynome(struct polynome * p, struct polynome * q)
{

	struct polynome* mp = creer_polynome(p->degre + q->degre + 1);
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

void detruire_polynome(struct polynome **p)
{
    free((*p)->coefficient);
    free(*p);
    *p = NULL;
}

struct polynome * additioner_polynome(const struct polynome * p,const struct polynome * q)
{

	struct polynome* ap = creer_polynome(p->degre + q->degre + 1);
	ap->degre = p->degre + q->degre;
    if (ap == NULL)
    {
        perror("Echec d'allocution");
        exit(2);
    }

    for (int i = 0; i < ap->taille; i++) {
		ap->coefficient[i] = 0;
	}
	for (int i = 0; i < p->taille; i++)
    {
        for (int j = 0; j < q->taille; j++)
        {
            ap->coefficient[i] += p->coefficient[i] + q->coefficient[j];
        }
    }
	return ap;
}

void detruire(struct polynome **p)
{
    free((*p)->coefficient);
    free(*p);
    *p = NULL;
}