#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "akermann.h"
#include "carbon.h"

double newton(double x, double e, double a)
{
    if (fabs(a*a-x) <= e)
    {
        return a;
    }
    else
    {
        return newton(x,e,((a+x/a)/2));
    }
}

double newtonNonRecurs(double x,double e, double a)
{
    while (fabs(a*a-x) > e)
    {
        a = ((a+x/a)/2);
    }
    return a;
}