/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */

/* declaration constantes et types utilisateurs */
#define N 50
/* declaration de fonctions utilisateurs */
unsigned long long int bin(unsigned n, unsigned p);
unsigned long long int bin_mem(unsigned n, unsigned p);
unsigned long long int bin_mem_2(unsigned long long **bin_tab, unsigned n, unsigned p);
unsigned long long int bin_ter_2(unsigned n, unsigned p, unsigned x, unsigned y);
unsigned long long int bin_ter(unsigned n, unsigned p);
unsigned long long int bin_iter(unsigned n, unsigned p);
/* fonction principale */
int main(int argc, char **argv)
{
    /* declaration et initialisation des variables */
    int n, p;
    /* ici faire quelque chose */
    if (argc != 3)
    {
        printf("Pas assez ou trop d'argument...\n");
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    p = atoi(argv[2]);
    printf("Binomial (%d, %d) = %llu (récursif naïf)\n\n", n, p, bin(n, p));
    printf("Binomial (%d, %d) = %llu (récursif avec mémoïsation)\n\n", n, p, bin_mem(n, p));
    printf("Binomial (%d, %d) = %llu (récusif terminal)\n\n", n, p, bin_ter(n, p));
    printf("Binomial (%d, %d) = %llu (itératif)\n\n", n, p, bin_iter(n, p));
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
unsigned long long int bin(unsigned n, unsigned p)
{
    static int i = 1;
    printf("[nbre d'appels = %d]\n", i++);
    if (p > n)
    {
        return 0;
    } 
    if (p == 0 || p == n)
    {
        return 1;
    } else {
        return bin(n-1, p) + bin(n-1, p-1);
    }
}

unsigned long long int bin_mem(unsigned n, unsigned p)
{
    unsigned long long int **bin_tab = malloc((n+1) * sizeof(unsigned long long int *));
    for (int i = 0; i <= n; i++) {
        *(bin_tab+i) = malloc((p+1) * sizeof(unsigned long long int));
    }
    return bin_mem_2(bin_tab, n, p);
}



unsigned long long int bin_mem_2(unsigned long long **bin_tab, unsigned n, unsigned p)
{
    static int i = 1;
    printf("[nbre d'appels = %d]\n", i++);
    if (p > n)
    {
        return 0;
    } 
    if (p == 0 || p == n)
    {
        return 1;
    }
    if (bin_tab[n][p] != 0)
    {
        return bin_tab[n][p];
    }
    bin_tab[n][p] = bin_mem_2(bin_tab, n-1, p) + bin_mem_2(bin_tab, n-1, p-1);
    return bin_tab[n][p];
}


unsigned long long int bin_ter(unsigned n, unsigned p)
{
    return bin_ter_2(n, p, 1, 1);
}

unsigned long long int bin_ter_2(unsigned n, unsigned p, unsigned x, unsigned y)
{
    static int i = 1;
    printf("[nbre d'appels = %d]\n", i++);
    if (p > n)
    {
        return 0;
    } 
    if (p == 0 || p == n)
    {
        return 1;
    } else {
        return bin_ter_2(n-1, p-1, x*n, y*p);
    }
}



unsigned long long int bin_iter(unsigned n, unsigned p)
{
    static int i = 1;
    printf("[nbre d'appels = %d]\n", i++);
    int coeff = 1;
    
    if (p > n - p) {
        p = n - p;
    }
    
    for (int i = 0; i < p; ++i) {
        coeff *= (n - i);
        coeff /= (i + 1);
    }
    
    return coeff;
}