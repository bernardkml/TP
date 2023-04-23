/* declaration de fonctionnalites supplementaires */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stdio.h> /* printf */

/* declaration constantes et types utilisateurs */

/* declaration de fonctions utilisateurs */
double puiss(double x, unsigned n);
double puiss_rap(double x, unsigned n);
double puiss_ter_2(double x, unsigned n, double acc);
double puiss_ter(double x, unsigned n);
double puiss_rap_ter_2(double x, unsigned n, double acc);
double puiss_rap_ter(double x, unsigned n);
/* fonction principale */
int main()
{
    /* declaration et initialisation des variables */
    double x = 2;
    int n = 6;
    /* ici faire quelque chose */
    printf("%g\n", puiss(x,n));
    printf("%g\n", puiss_rap(x,n));
    printf("%g\n", puiss_ter(x, n));
    printf("%g\n", puiss_rap_ter(x,n));
    /* valeur fonction */
    return EXIT_SUCCESS;
}

/* definitions des fonctions utilisateurs */
double puiss(double x, unsigned n)
{
    static int i = 1;
    printf("Appel n°%d\n", i++);
    if (n == 0)
    {
        return 1;
    } else {
        return x * puiss(x,n-1);
    }
}

double puiss_rap(double x, unsigned n)
{
    static int i = 1;
    printf("Appel n°%d\n", i++);
    if (n == 0)
    {
        return 1;
    }
    if (n%2 == 0)
    {
        return puiss_rap(x*x, n/2);
    } else {
        return puiss_rap(x*x, (n-1)/2)*x;
    }
}

double puiss_ter_2(double x, unsigned n, double acc)
{
    if (n == 0)
    {
        return acc;
    } else {
        return puiss_ter_2(x, n-1,x*acc);
    }
}

double puiss_ter(double x, unsigned n)
{
    static int i = 1;
    printf("Appel n°%d\n", i++);
    return puiss_ter_2(x, n, 1);
}

double puiss_rap_ter_2(double x, unsigned n, double acc)
{
    if (n == 0)
    {
        return acc;
    }
    
    if (n%2 == 0)
    {
        return puiss_rap_ter_2(x*x,n/2,acc);
    } else {
        return puiss_rap_ter_2(x*x,(n-1)/2,acc)*x;
    }
}

double puiss_rap_ter(double x, unsigned n)
{
    static int i = 1;
    printf("Appel n°%d\n", i++);
    return puiss_rap_ter_2(x, n, 1);
}