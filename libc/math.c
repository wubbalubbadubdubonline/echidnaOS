#include "math.h"

double pow(double x, double y)
{
	double res = 1;

	for ( int i = (int)y; i > 0; i-- )
		res *= x;

	return res;
}