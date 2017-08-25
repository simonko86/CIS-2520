#include <stdio.h>
#include <string.h>
#include <time.h>

int permutation(void);
int akermann(int m,int n);
double newton(double x,double e, double a);
double newtonNonRecurs(double x,double e, double a);

int main (void){

	char ch;
	int m,n;
	int akermannAns;

    double x,e,a;
    double newtonAns, newtonNonRecursAns;

    //float start,end,seconds;
    float seconds, seconds_recurs;

	printf("Press key to display all permutations of carbon\n");
	ch = getchar();
	permutation();

	printf("Which numbers for Akermann function?\n");
	printf("Note: largest combination tested was m=4,n=3\n");
	printf("What number for m?\n");
	scanf("%d",&m);
	printf("What number for n?\n");
	scanf("%d",&n);
	akermannAns = akermann(m,n);
	printf("akermannAns = %d\n", akermannAns);

	printf("What number for x?\n");
	scanf("%lf",&x);
	printf("What number for e?\n");
	scanf("%lf",&e);
	printf("What number for a?\n");
	scanf("%lf",&a);

	clock_t start = clock();
    newtonAns = newton(x,e,a);
    clock_t end = clock();
    seconds = (float)(end - start) / (CLOCKS_PER_SEC/1000000);//nano
    printf("Using recursive: The approximation is: %fmS\n",newtonAns);
    printf("Execution time of recursive: %f \n",seconds);

	clock_t start_recurs = clock();
    newtonNonRecursAns = newtonNonRecurs(x,e,a);
    clock_t end_recurs = clock();
    seconds_recurs = (float)(end_recurs - start_recurs) / (CLOCKS_PER_SEC/1000000);
    printf("Using non-recursive: The approximation is: %fmS\n",newtonNonRecursAns);
    printf("Execution time of nonrecursive: %f \n",seconds_recurs);

	return 0;
}

double newton(double x,double e, double a)
{
    if (a*a-x <= e)
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
    while (a*a-x > e)
    {
        a = (x,e,((a+x/a)/2));
    }
    return a;
}

int akermann(int m,int n)
{
    int result;
    
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

int permutation(void) {

	int c = 1;
	int a = 2;
	int r = 3;
	int b = 4;
	int o = 5;
	int n = 6;
	char str[6] =" ";
	int swap,count = 0;
	
	for (c=1;c<=6;c++)
	{
	    for (a=1;a<=6;a++)
	    {
       	    for (r=1;r<=6;r++)
	            {
	       	        for (b=1;b<=6;b++)
	                {
	       	            for (o=1;o<=6;o++)
	                    {
	       	                for (n=1;n<=6;n++)
	                        {
	                            if (c!=a && c!= r && c!=b && c!=o && c!=n &&
	                            a!=c && a!=r && a!=b && a!=o && a!=n &&
	                            r!=c && r!=a && r!=b && r!=o && r!=n &&
	                            b!=c && b!=a && b!=r && b!=o && b!=n &&
	                            o!=c && o!=a && o!=r && o!=b && o!=n &&
	                            n!=c && n!=a && n!=r && n!=b && n!=o)
	                            {
    	                            for(swap=1;swap<7;swap++)
    	                            {
    	                                if(c==swap)
    	                                {
                                            str[swap]='C';
    	                                }
    	                                if(a==swap)
    	                                {
                                            str[swap]='A';
    	                                }
    	                                if(r==swap)
    	                                {
                                            str[swap]='R';
    	                                }
    	                                if(b==swap)
    	                                {
                                            str[swap]='B';
    	                                }
    	                                if(o==swap)
    	                                {
                                            str[swap]='O';
    	                                }
    	                                if(n==swap)
    	                                {
                                            str[swap]='N';
    	                                }
	                                }
	                                printf("%s\n",str);
	                                count++;

	                            }
	                        }
	                    }
	                }
	            }
	    }
	}
	printf("Count: %d\n",count);
	return 0;
}

