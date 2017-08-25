#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <math.h>

#include "akermann.h"
#include "carbon.h"
#include "newton.h"


int main (void){

	char ch;
	long m,n,akermannAns;
    int count = 1;

    double x,e,a;
    double newtonAns, newtonNonRecursAns;

    struct timeb startTime;
    struct timeb endTime;
    struct timeb startTimeNon;
    struct timeb endTimeNon;

    float delta;
    float deltaNonRecurs;

	printf("Press any key to display all permutations of carbon or 'x' to exit\n");
	ch = getchar();
    if (ch == 'x')
    {
        return -1;
    }
	permutation();

    while(count <= 3)
    {
    	printf("Which numbers for Akermann function?\n");
    	printf("Note: largest combination tested was m=3,n=14 =131069. Any higher and seg fault\n");
    	printf("What number for m?\n");
    	scanf("%ld",&m);
    	printf("What number for n?\n");
    	scanf("%ld",&n);
    	akermannAns = akermann(m,n);
    	printf("Attempt: %d. AkermannAns = %ld\n", count,akermannAns);
        count++;
    }
    printf("Newton's method\n");
	printf("What number for x?\n");
	scanf("%lf",&x);
	printf("What number for e?\n");
	scanf("%lf",&e);
    printf("What number for a?\n");
    scanf("%lf",&a);

    ftime(&startTime);
    for (int i = 0; i < 10000000; i++)
    {
        newtonAns = newton(x,e,a);
    }
    ftime(&endTime);
    delta = ((endTime.time - startTime.time)*100 + (endTime.millitm - startTime.millitm));
    printf("Using recursive: The approximation is: %f\n",newtonAns);
    printf("Execution time: %f\n", fabs(delta));
    ftime(&startTimeNon);
    for (int i = 0; i < 10000000; i++)
    {
        newtonNonRecursAns = newton(x,e,a);
    }
    ftime(&endTimeNon);

    deltaNonRecurs = ((endTimeNon.time - startTimeNon.time)*100 + (endTimeNon.millitm - startTimeNon.millitm));
    printf("Using non-recursive: The approximation is: %f\n",newtonNonRecursAns);
    printf("Execution time: %f\n", fabs(deltaNonRecurs));

    printf("Each function was repeated 10,000,000 times to provide a difference in approximation times\n");
    if(delta > deltaNonRecurs)
    {
        printf("Recursion is faster than iterive\n");
        printf("The difference between the two is %f mS\n", fabs(delta-deltaNonRecurs));
    }
    else if (deltaNonRecurs > delta)
    {        
        printf("Nonecursion is faster than recursion\n");
        printf("The difference between the two is %f mS\n", fabs(deltaNonRecurs-delta));
    }
    else
    {
        printf("The difference between the two is 0mS\n");
        printf("Neither is faster\n");
    }
	return 0;
}




