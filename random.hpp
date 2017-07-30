#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <ctime> 

using namespace std;

double randomDouble();
int randomInterval(int a, int b, int extraSeed = 0);

#endif
