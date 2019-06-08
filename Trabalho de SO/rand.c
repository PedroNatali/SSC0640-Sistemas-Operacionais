/**
 * http://en.wikipedia.org/wiki/Linear_congruential_generator
 * 
 * Veja a relação de recorrência do link acima.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const unsigned int A = 1664525, C = 1013904223;

unsigned int next(unsigned int x)
{
        return x*A+C;
}

int main()
{
	unsigned int x = time(NULL);
	double y;
	
	for (int i = 0; i < 100; ++i)
	{
		x = next(x);
		y = (double)x/8000000000;

		printf("%f\n", y);
	}
	
	return 0;
}

