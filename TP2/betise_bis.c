#include <stdio.h>

void f(int n)
{
  printf("%d\n", n);
  return f(n);
}

int main ()
{
  f(0);
  return 0;
}
