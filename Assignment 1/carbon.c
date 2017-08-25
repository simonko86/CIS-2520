#include <stdio.h>
#include <string.h>
#include <time.h>

#include "akermann.h"
#include "newton.h"

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
