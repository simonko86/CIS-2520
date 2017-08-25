/**************************
*Simon Ko 0906762
*Due: 10/17/2016
*Completed: 10/15/2016
*Postfix program involving 
*push and pop of stack
*
**************************/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stack[50]; //Stack size array is 50 elements
int top = -1;

/*
*Pushing eaelement element into the stack
*/

int push(int element)
{
	if (top == 50)
	{
		printf("Stack full\n");
		exit(0);
	}
	else
	{
		stack[++top] = element;
		return stack[top];
	}
}

/*
*Popping the top element from the stack
*/

int pop()
{
	if (top == -1)
	{
		printf("Stack empty\n");
		exit(0);
	}
	else
	{
		return(stack[top--]);
	}
}

int main(int argc, char const *argv[])
{
	char element;
	int i = 0;
	int first,second;
	char postFixExpression[50];

	if ((argc < 2) ||(argc > 3)) //if command input is incorrect
	{
		printf("Incorrect number of arguments\n");
		return -1;
	}
	strcpy(postFixExpression, argv[1]); //copy the expression to char array

	while((element=postFixExpression[i++]) != '\0')
	{

		if(isdigit(element)) //if the element is a digit then push into stack
		{
			push(element-'0');	
		}
		else
		{
			second = pop(); //if not then pop the first two elements
			first = pop();
			switch(element) //depending on the symbol, then do the expression and push back to stack
			{
				case '+':
					push(first+second);
				break;
				case '-':
					push(first-second);
				break;
				case '*':
					push(first*second);
				break;
				case '/':
					push(first/second);
				break;
				default:
					printf("Incorrect operator\n");
					return -1;
				break;
			}
		}
	}
	printf("Result: %d\n", stack[top]); //print off top of stack
	return 0;
}