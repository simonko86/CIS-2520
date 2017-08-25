/**************************
*Simon Ko 0906762
*Due: 11/7/2016
*Completed: 11/6/2016
*Menu based program that can:
*Prefix,postfix,infix display
*Can update unknown variables with a number
*Can perform calculations too
*Cannot display an expression tree
**************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

float stackNumber[50];
int stackOperator[50];
int topNum = -1;
int topOp = -1;

float pushNumber(float element)//stack for numbers
{
	if (topNum == 50)
	{
		printf("Stack full\n");
		exit(0);
	}
	else
	{
		stackNumber[++topNum] = element;
		return stackNumber[topNum];
	}
}

char pushOperator(char element)//seperate stack for operands
{
	if (topOp == 50)
	{
		printf("Stack full\n");
		exit(0);
	}
	else
	{
		stackOperator[++topOp] = element;
		return stackOperator[topOp];
	}
}

char popOperator() //push the operand stack
{
	if (topOp == -1)
	{
		printf("Stack empty\n");
		exit(0);
	}
	else
	{
		return(stackOperator[topOp--]);
	}
}
float popNumber() //push the floats stack
{
	if (topNum == -1)
	{
		printf("Stack empty\n");
		exit(0);
	}
	else
	{
		return(stackNumber[topNum--]);
	}
}
/*Started to do expression tree */
typedef struct element
{
	char *info;
	struct element *right;
	struct element *left;
}element;

element* makeElement(char *information)
{
	element *temp;
	temp = malloc(sizeof(struct element)+1);
	temp->info = malloc(sizeof(char)*(strlen(information)+1));
	strcpy(temp->info, information);
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}

element* addtoList(element *theList, element* toBeAdded, char* direction)
{
	element *tempPtr = toBeAdded;
	if (theList == NULL)
	{
		theList = tempPtr;
		return theList;
	}

	if (strcmp(direction,"right") == 0)
	{
		tempPtr->right = theList;
		theList = toBeAdded;
		return theList;
	}
	else
	{
		tempPtr->right = theList;
		theList = toBeAdded;
		return theList;
	}
}

int main(int argc, char const *argv[])
{
	//char expression[50] = "(((x1+5.12)*(x2-7.68))/x3)"; //tested expression
	char expression[50];
	int userChoice = 1;
	char character;
	char poppedOperator;
	float poppedNumber;
	char realExpres[50];
	char tempStr[5];
	char tempStr2[2];
	float f;
	int j=0;
	int expressionLength = strlen(expression);
	float first = 0.00;
	float second = 0.00;
	int count = 1;
	char c,d;
	char varName[2];
	char xVar[3];

	if ((argc < 2) ||(argc > 3)) //if command input is incorrect
	{
		printf("Incorrect number of arguments\n");
		return -1;
	}

	strcpy(expression,argv[1]);

	while(userChoice != 0)
	{
			printf("\n");
			printf("1. Display\n");
			printf("2. Preorder\n");
			printf("3. Inorder\n");
			printf("4. Postorder\n");
			printf("5. Update\n");
			printf("6. Calculate\n");
			printf("7. Exit\n");
			scanf("%d",&userChoice);

		switch(userChoice)
		{

		case 1:
			printf("Display\n");
			printf("%s\n",expression );
			//printf("Use preorder: %s\n", preorder);

			//if expression, add new node, right leaf
			//if variable, add to right leaf. if node is full, add to left leaf
			//otherwise up a tree, and add to left leaf
		break;
		case 2://print the order of the expression but replace any operand with the earliest open bracket in the expression
			printf("Preorder\n");
			poppedOperator = ')';
			expressionLength = strlen(expression);
			strcpy(realExpres,expression);
			for (int i = 0; i < expressionLength; ++i)
			{
				c = expression[i];
				if ((c == '+') || (c == '/') || (c == '-') || (c == '*'))
				{
					expression[i] = ' '; //replace open bracket with a space 
					for (int j = i; j >= 0; j--) //count down from that point
					{
						d = expression[j]; //when coming to first open bracket
						if (d == '(' && count == 1)
						{
							expression[j] = c; //replace with the operand
							count++;
						}
					}
				}
					count = 1;
			}
			for (int i = 0; i < expressionLength; ++i)
			{
				c = expression[i];
				if (c == ')')
				{
					//don't print the bracket
				}
				else
				{
					printf("%c",c ); //print the character
				}
			}
			strcpy(expression,realExpres);
		break;
		case 3://good
			printf("Inorder\n");
			expressionLength = strlen(expression);
			strcpy(realExpres,expression);
			for (int i = 0; i < expressionLength; ++i)
			{
				character = expression[i];
				if ((character == '(') || (character == ')')) //ignore printing these brackets
				{
				}
				else
				{
					printf("%c", character);	
				}
			}

			strcpy(expression,realExpres);
		break;
		case 4://good
			printf("Postorder\n");
			expressionLength = strlen(expression);
			strcpy(realExpres,expression);
			poppedOperator = ')';
			for (int i = 0; i < expressionLength; ++i)
			{
				character = expression[i];

				if (isdigit(character)) //if it's a number, push into stack
				{
					memcpy(tempStr, &expression[i],4);
					tempStr[4] = '\0';
					f = atof(tempStr);
					i += 3;			
					pushNumber(f);
				}
				else if (character == 'x') //if it's an unknown variable, push 0.00 into the stack
				{
					memcpy(tempStr2, &expression[i],3);
					tempStr2[2] = '\0';
					f = 0.00;
					pushNumber(f);
					i += 1;					
				}
				else if ((character == '+') || (character == '-') || (character == '/') || (character == '*') || (character == '('))
				{
					pushOperator(character); //push any operator into the stack
				}
				else //character is )
				{
					realExpres[j] = character;
					j++;

					while (topNum != -1)
					{
						poppedNumber = popNumber();
						printf("%.2f ", poppedNumber );//keep on popping numbers
					}
					while (topOp != -1)
					{ //keep popping characters until before )
						poppedOperator = popOperator();
						if (poppedOperator != '(')
						{
							printf("%c ", poppedOperator);	
						}
					}
				}
			}
			strcpy(expression,realExpres);
		break;
		case 5://good

			expressionLength = strlen(expression)+1;
			printf("Update %s\n",expression);
			printf("variable name\n");
			scanf("%s",varName);
			printf("new variable\n");
			scanf("%s",xVar);
			j=0;
			for (int i = 0; i < 50; ++i)
			{
				character = expression[i];
				realExpres[j] = expression[i];
				j++;
				if (character == 'x')
				{
					memcpy(tempStr2, &expression[i],3);
					tempStr2[2] = '\0';
					if(strcmp(tempStr2, varName) == 0)
					{
						j--;
						realExpres[j] = xVar[0];
						j++;
						realExpres[j] = xVar[1];
						j++;
						realExpres[j] = xVar[2];
						j++;
						realExpres[j] = xVar[3];
						j++; //replace any matching variable with the number associated
					}
					else
					{
						j--;
						realExpres[j] = tempStr2[0];
						j++;
						realExpres[j] = tempStr2[1];
						j++; //if no match, then just put the variable back in
					}

					i += 1;					
				}
				
			}
			realExpres[j] = '\0'; //add null
			j=0;
			while(realExpres[j] != '\0')
			{
				expression[j] = realExpres[j];//switch back to expression
				j++;
			}
			expression[j] = '\0';
			printf("Changed expression: %s\n",expression );


			break;
		case 6://good
			printf("Calculate\n"); //use code from part 2 assignment 2. Convert expression to postfix, then calculate
			expressionLength = strlen(expression);
			poppedOperator = ')';
			for (int i = 0; i < expressionLength; ++i)
			{
				character = expression[i];

				if (isdigit(character))
				{
					memcpy(tempStr, &expression[i],4);
					tempStr[4] = '\0';
					f = atof(tempStr);
					i += 3;			
					pushNumber(f);
				}
				else if (character == 'x')
				{
					memcpy(tempStr2, &expression[i],3);
					tempStr2[2] = '\0';
					f = 0.00;
					pushNumber(f);
					i += 1;
					
				}
				else if ((character == '+') || (character == '-') || (character == '/') || (character == '*'))
				{
					pushOperator(character);
				}
				else if(character == '(')
				{
					//don't do anything
				}
				else //character is )
				{
						second = popNumber();
						first = popNumber();
						poppedOperator = popOperator();
						switch(poppedOperator)
						{
							case '+':					
								pushNumber(first+second);
							break;
							case '-':
								pushNumber(first-second);
							break;
							case '*':
								pushNumber(first*second);
							break;
							case '/':
								pushNumber(first/second);
							break;
							case '(':
								//do nothing
							break;
							default:
								printf("Incorrect somewhere\n");
								return -1;
							break;

						}
				}
			}
			printf("Result: %.2f\n", stackNumber[topNum]);
		break;
		case 7://good
			printf("Exit\n");
			return 0;
		break;
		default:
		printf("Incorrect operation\n");
		break;
		}
	}

	return 0;
}