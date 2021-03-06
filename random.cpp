#include "random.hpp"   
   
double randomDouble()
{
   srand((unsigned)time(0));
   return (rand() / (double)RAND_MAX);
}

int randomInterval(int a, int b, int extraSeed) // if seed negative don't srand
{
   if (extraSeed >= 0)
      srand((unsigned)(time(0)+extraSeed));
   double r = rand() / (double)RAND_MAX;
   int interval = b - a + 1;
   return (a + (int)(interval*r));
}
