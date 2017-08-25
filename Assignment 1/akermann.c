#include <stdio.h>
#include <string.h>
#include <time.h>

#include "carbon.h"
#include "newton.h"


long akermann(long m,long n)
{
    long result = 0;
    
    if (m == 0)
    {
        result = n+1;
        return result;
    }
    else if (n == 0)
    {
        return akermann(m-1,1);
    }
    else
    {
        return akermann(m-1,akermann(m,n-1));
    }

}