#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct polynome {
	int * coefficients;
	int taille;
	int degre;
};

struct polynome * creer_polynome (int);
struct polynome * initialiser_polynome_alea (int);
void reformater_polynome (struct polynome *);
void scalaire_polynome (struct polynome *, int);
struct polynome * additionner_polynome (const struct polynome *, const struct polynome *);
struct polynome * multiplier_polynome (const struct polynome *, const struct polynome *);
struct polynome * deriver_polynome (const struct polynome *);
void detruire_polynome (struct polynome **);
void afficher_polynome (const struct polynome *);
struct polynome * multiplier_X (struct polynome *);
void usage_polynome(char []);

int main(int argc, char ** argv){

	struct polynome *p, *x, *dp, *xp, *dxp, *xdp, *q, *pq, *t;
	int degre_p, degre_q;
	if (argc != 3) {
		perror("Wssshhhh t'es betes ou quoi 🤣🤣🫵🫵 !!!!\n");
		usage_polynome(argv[0]);
		return EXIT_FAILURE;
	}

	degre_p = strtol(argv[1], NULL, 10);
	degre_q = strtol(argv[2], NULL, 10);
	if (degre_p < -1 || degre_q < -1) {
		perror("Erreur. Degré d'un polynôme ≥ -1 !");
		return EXIT_FAILURE;
	}
	if (degre_p < degre_q) {
		int tmp = degre_p;
		degre_p = degre_q;
		degre_q = tmp;
	}

	/* Test Barmann-Fock */
	printf("\nCommutateur des opérateurs d/dx et x (Bargmann-Fock) \n");
	x = creer_polynome (EXIT_FAILURE);
	x->coefficients[0] = 0;
	x->coefficients[1] = 1;
	x->degre = 1; /* polynôme X */
	srand (time(NULL));
	p = initialiser_polynome_alea (degre_p);
	printf ("p (de degré %d) = ", p->degre);
	afficher_polynome (p);
	xp = multiplier_polynome (x, p);
	printf("x.p (de degré %d) = ", xp->degre);
	afficher_polynome (xp);
	dxp = deriver_polynome (xp);
	printf("d(x.p)/dx (de degré %d) = ", dxp->degre);
	afficher_polynome (dxp);
	dp = deriver_polynome (p);
	printf("dp/dx (de degré %d) = ", dp->degre);
	afficher_polynome (dp);
	xdp = multiplier_polynome (x, dp);
	printf("x.dp/dx (de degré %d) = ", xdp->degre);
	afficher_polynome (xdp);
	scalaire_polynome (xdp, -1);
	printf ("-x.dp/dx (de degré %d) = ", xdp->degre);
	afficher_polynome (xdp);
	q = additionner_polynome (dxp, xdp);
	printf ("d(x.p)/dx - x*d(p/dx) (de degré %d) = ", q->degre);
	afficher_polynome (q);
	scalaire_polynome (q, -1);
	t = additionner_polynome (p, q);
	printf ("p - [d(x.p)/dx - x*d(p/dx)] (de degré %d) = ", t->degre);
	afficher_polynome (t);

	/* Nettoyage */
	printf("Ménage mémoire...\n");
	detruire_polynome(&t);
	detruire_polynome(&q);
	detruire_polynome(&dp);
	detruire_polynome(&xdp);
	detruire_polynome(&xp);
	detruire_polynome(&dxp);
	detruire_polynome(&x);

	/* Test multiplication */
	printf("\nMultiplication de deux polynômes \n");
	printf ("p (de degré %d) = ", p->degre);
	afficher_polynome (p);
	q = initialiser_polynome_alea (degre_q);
	printf ("q (de degré %d) = ", q->degre);
	afficher_polynome (q);
	pq = multiplier_polynome (p, q);
	printf("p.q (de degré %d) = ", pq->degre);
	afficher_polynome (pq);

	/* Nettoyage */
	printf("Ménage mémoire...\n");
	detruire_polynome(&pq);
	detruire_polynome(&p);

	printf("Au revoir !\n");

	return EXIT_SUCCESS;
}

struct polynome * creer_polynome (int taille) {
	struct polynome * res = malloc(sizeof(struct polynome));
	if (res == NULL) {
		perror("Échec de l'allocation mémoire pour la structure ");
		exit(EXIT_FAILURE);
	}
	res->coefficients = calloc(taille, sizeof(int));
	if (taille > 0 && res->coefficients == NULL) {
		perror("Échec de l'allocation mémoire pour les coefficients ");
		exit(EXIT_FAILURE);
	}
	res->degre = -1;
	res->taille = taille;
	return res;
}

struct polynome * initialiser_polynome_alea (int degre_max) {
	struct polynome *res;
	res = creer_polynome (degre_max + 1);
	int i;
	res->degre = -1;
	for (i = 0; i < res->taille; ++i) {
		res->coefficients[i] =  (rand()%2 ? -1 : 1) * rand()%10;
		if (res->coefficients[i] != 0) { res->degre = i; }
	}
	reformater_polynome(res);
	return res;
}

void reformater_polynome (struct polynome * p) {
	int i;
	if (p->taille > p->degre + 1) {
		int * nouv_coeff = malloc((p->degre + 1) * sizeof(int));
		if (p->degre >= 0 && nouv_coeff == NULL) {
			perror("Échec de la réallocation mémoire pour les coefficients");
			exit(EXIT_FAILURE);
		}
		p->taille = p->degre + 1;
		for (i = 0; i <= p->degre; ++i) {
			nouv_coeff[i] = p->coefficients[i];
		}
		free(p->coefficients);
		p->coefficients = nouv_coeff;
	}
}

void scalaire_polynome (struct polynome* p, int a) {
	int i;
	if (a != 0) {
		for (i = 0; i <= p->degre; ++i)
			p->coefficients[i] *= a;
	}
	else {
		p->degre = -1;
		reformater_polynome(p);
	}
}

struct polynome * additionner_polynome (const struct polynome *p, const struct polynome *q) {
	int i, d_min, d_max, *r_max;
	struct polynome * res ;
	if (p->degre < q->degre) {
		r_max = q->coefficients;
		d_min = p->degre;
		d_max = q->degre;
	}
	else {
		r_max = p->coefficients;
		d_min = q->degre;
		d_max = p->degre;
	}
	res = creer_polynome(d_max + 1);
	for (i = 0; i <= d_min; ++i) {
		res->coefficients[i] = p->coefficients[i] + q->coefficients[i];
	}
	for ( ; i <= d_max; ++i) {
		res->coefficients[i] = r_max[i];
	}
	res->degre = d_max;
	while ((res->degre >=0) && (res->coefficients[res->degre]==0)) {
			res->degre--;
	}
	reformater_polynome(res);
	return res;
}

struct polynome * multiplier_polynome (const struct polynome *p, const struct polynome *q) {
	int i,j;
	struct polynome *res;
	if (p->degre < 0 || q->degre < 0) {
		return creer_polynome(0);
	}
	res = creer_polynome(p->degre + q->degre + 1);
	res->degre = res->taille - 1;
	for (i = 0; i <= res->degre; ++i)
		res->coefficients[i] = 0;
	for (i = 0; i <= p->degre; ++i)
		for (j = 0; j <= q->degre; ++j)
			res->coefficients[i+j] += p->coefficients[i] * q->coefficients[j];
	return res;
}

struct polynome * deriver_polynome (const struct polynome *p) {
	int i;
	struct polynome * res;
	if (p->degre <= 0) {
		res = creer_polynome(0);
		return res;
	}
	res = creer_polynome(p->degre);
	res->degre = p->degre == -1 ? -1 : p->degre - 1;
	for (i=0; i <= res->degre; ++i)
		res->coefficients[i] = (i+1) * p->coefficients[i+1];
	reformater_polynome (res);
	return res;
}

void detruire_polynome (struct polynome **p){
	free((*p)->coefficients);
	free(*p);
	*p = NULL;
}

void afficher_polynome (const struct polynome *p) {
	int i = p->degre;
	if (p->degre < 0) {
		printf("0\n");
		return;
	}
	printf("%s ", p->coefficients[i] < 0 ? "-" : "");
	if (abs(p->coefficients[i]) != 1) printf("%d", abs(p->coefficients[i]));
	if (i > 0) printf("X");
	if (i > 1) printf("^%d", i);
	printf(" ");
	for (i = p->degre - 1; i >= 0; i--) {
		if (p->coefficients[i] != 0) {
			printf("%s ", p->coefficients[i] < 0 ? "-" : "+");
			if (abs(p->coefficients[i]) != 1 || i == 0) printf("%d", abs(p->coefficients[i]));
			if (i > 0) printf("X");
			if (i > 1) printf("^%d", i);
			printf(" ");
		}
	}
	printf("\n");
}

/** Fonction qui alloue de l'espace et renvoie l'adresse */
/* d'un polynôme égal au produit de p par le monôme X */
struct polynome * multiplier_X (struct polynome * p) {
	int i;
	struct polynome * xp;
	if (p->degre < 0) {return creer_polynome(0); }
	xp = creer_polynome(p->degre + 2);
	xp->degre = p->degre + 1;
	xp->coefficients[0] = 0;
	for (i = 1; i <= xp->degre; ++i) {
		xp->coefficients[i] = p->coefficients[i-1];
	}
	return xp;
}

void usage_polynome(char cmd[]) {
	printf("Usage: %s int int\n", cmd);
	printf("Argument 1 (int ≥ -1) : degré max \n");
	printf("Argument 2 (int ≥ -1) : degré min \n");
}