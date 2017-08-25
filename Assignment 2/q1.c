/**************************
*Simon Ko 0906762
*Due: 10/17/2016
*Completed: 10/14/2016
*Car rental program using
*multiple structs
*and manipulation of them
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----NODE----//
/*
*Structure of the node
*/
typedef struct cars
{
	int returnDate;
	char *registration;
	int miles;
	struct cars *next;
}cars;

/*
*Constucts a node to add to the list
*/
cars* makeCar(int mileage, char * license, int rDate)
{
	cars *vehicle;
	vehicle = malloc(sizeof(struct cars));
	vehicle->registration = malloc(sizeof(char)*(strlen(license)+1));
	vehicle->miles = mileage;
	strcpy(vehicle->registration, license);
	vehicle->returnDate = rDate;
	vehicle->next = NULL;
	return vehicle;
}

//----LINKED LIST ----//
/*
*Adds a node to the list and returns the list
*/
cars* addtoList(cars *theList, cars *toBeAdded) 
{
	cars * tempPtr = toBeAdded;

	if (theList == NULL)
	{
		theList = toBeAdded ;
		return theList;
	}

	tempPtr->next = theList; 
	theList = toBeAdded; 
	return theList;
}
/*
*Prints the whole list, and loops through each node until the end
*/
void printList(cars *theList)
{
	cars* head = theList;

	if (head == NULL)
	{
		printf("List is empty\n");
		return;
	}

	while(head->next != NULL)
	{
		printf("License: %s Mileage: %d Return date: %d\n",head->registration, head->miles,head->returnDate );
		head = head->next;
	}
	return;
}

cars* getHead(cars *theList)
{
	cars* head = malloc(sizeof(struct cars));
	head = theList;
	return head;
}

/*
*This function sorts the list by switching two nodes depending on if the mileage is greater.
*To get a completed sorted list, the list has to traverse length of the list times.
*Therefore a while loop finds the length of list, and that number is used to find out how many
*iterations is needed
*/
void sortMileage(cars *theList)
{
	cars *current=theList;
	cars *head=theList;
	int tempMile;
	char *tempPlate;
	int tempReturnDate;
	int count = 0;

	while(current->next != NULL)
	{
		count++;
		current = current->next;
	}
	//loop through list x times to make sure they're all in order
	for (int i = 0; i < count-1; ++i)
	{
		current=head;
		while (current->next->next != NULL)
		{
			if(current->miles > current->next->miles)
			{
				tempMile = current->miles;
				tempPlate = current->registration;
				tempReturnDate = current->returnDate;

				current->miles=current->next->miles;
				current->registration=current->next->registration;
				current->returnDate=current->next->returnDate;

				current->next->miles=tempMile;
				current->next->registration=tempPlate;
				current->next->returnDate=tempReturnDate;
			}
				current=current->next;
		}
	}
	return;

}
/*
*This function sorts the list by switching two nodes depending on if the return date is greater.
*To get a completed sorted list, the list has to traverse length of the list times.
*Therefore a while loop finds the length of list, and that number is used to find out how many
*iterations is needed
*/
void sortReturnDate(cars *theList)
{
	cars *current=theList;
	cars *head=theList;
	int tempMile;
	char *tempPlate;
	int tempReturnDate;
	int count = 0;

	while(current->next != NULL)
	{
		count++;
		current = current->next;
	}
	//loop through list x times to make sure they're all in order
	for (int i = 0; i < count-1; ++i)
	{
		current=head;
		while (current->next->next != NULL)
		{
			if(current->returnDate > current->next->returnDate)
			{
				tempMile = current->miles;
				tempPlate = current->registration;
				tempReturnDate = current->returnDate;

				current->miles=current->next->miles;
				current->registration=current->next->registration;
				current->returnDate=current->next->returnDate;

				current->next->miles=tempMile;
				current->next->registration=tempPlate;
				current->next->returnDate=tempReturnDate;
			}
				current=current->next;
		}
	}
	return;
}        
/*
*This function finds a plate and returns the mileage of that
* vehicle. If it does not find that vehicle, it returns 0.
*/
int searchOriginalMileage(cars *theList, char * plate)
{
	cars* tempPtr = theList;
	int original = 0;

	while(tempPtr->next != NULL)
	{
		if(strcmp(plate,tempPtr->registration) == 0)
		{
			original = tempPtr->miles;
			return original;
		}
			tempPtr = tempPtr->next;
	}
	return 0;	
}
/*
*This function removes a car from the node if the plate matches any in the list.
*It points the previous node to the next node, and frees the current node
*/
void removeCar(cars *theList, char *plate)
{
	cars* current = theList;
	cars* previous = theList;
	while(previous->next != NULL)
	{
		current = current->next;
		if(strcmp(plate,previous->registration) == 0) //if plate matches
		{
				previous->returnDate = current->returnDate;
				previous->miles = current->miles;
				previous->registration = current->registration;
				previous->next = current->next;
				free(current);
				return;
		} 
		previous = previous->next;		
	}	
	return;	
}
/*
*This function will read the current cars in the available list denoted by first word in the line: Available
*/
cars* readFileAvail(cars *theList)
{
	cars* car = malloc(sizeof (struct cars));
	FILE *file;
	char word[255];
	char * token;

	file = fopen("test.txt","r");

	while( fgets (word, 255, file) != NULL)
	{
		char * license;
		char * milesChar;
		char * returnChar;
		int miles;
		int returnDate;
		token = strtok(word, " , ");

		if(strcmp(token, "Available") == 0)
		{
			milesChar = strtok(NULL," , ");
			license = strtok(NULL, " , ");
			returnChar = strtok(NULL, " , ");


			if (license == NULL)
			{
				return theList;
			}
			else
			{
				miles = atoi(milesChar);
				returnDate = atoi(returnChar);
				car = makeCar(miles,license,returnDate);
				theList = addtoList(theList, car);
			}
		}
	}
		fclose(file);
		return theList;

}
/*
*This function will read the current cars in the rented list denoted by first word in the line: Rented
*/
cars* readFileRented(cars *theList)
{
	cars* car = malloc(sizeof (struct cars));
	FILE *file;
	char word[255];
	char * token;

	file = fopen("test.txt","r");

	while( fgets (word, 255, file) != NULL)
	{
		char * license;
		char * milesChar;
		char * returnChar;
		int miles;
		int returnDate;
		token = strtok(word, " , ");

		if(strcmp(token, "Rented") == 0)
		{
			milesChar = strtok(NULL," , ");
			license = strtok(NULL, " , ");
			returnChar = strtok(NULL, " , ");


			if (license == NULL)
			{
				return theList;
			}
			else
			{
				miles = atoi(milesChar);
				returnDate = atoi(returnChar);
				car = makeCar(miles,license,returnDate);
				theList = addtoList(theList, car);
			}
		}
	}
		fclose(file);
		return theList;

}
/*
*This function will read the current cars in the repair list denoted by first word in the line: Repair
*/
cars* readFileRepair(cars *theList)
{
	cars* car = malloc(sizeof (struct cars));
	FILE *file;
	char word[255];
	char * token;

	file = fopen("test.txt","r");

	while( fgets (word, 255, file) != NULL)
	{
		char * license;
		char * milesChar;
		char * returnChar;
		int miles;
		int returnDate;
		token = strtok(word, " , ");

		if(strcmp(token, "Repair") == 0)
		{
			milesChar = strtok(NULL," , ");
			license = strtok(NULL, " , ");
			returnChar = strtok(NULL, " , ");


			if (license == NULL)
			{
				return theList;
			}
			else
			{
				miles = atoi(milesChar);
				returnDate = atoi(returnChar);
				car = makeCar(miles,license,returnDate);
				theList = addtoList(theList, car);
			}
		}
	}
		fclose(file);
		return theList;

}
/*
this will print the each list and write that into a file and then close the file pointer
*/
void printToFile(cars* theList, cars *theList2, cars *theList3)
{
	FILE *file;
	cars* head = theList;
	cars* head2 = theList2;
	cars* head3 = theList3;
	file = fopen("test.txt","w");
	while(head->next != NULL)
	{
		fprintf(file, "Available,%d,%s,%d\n", head->miles,head->registration,head->returnDate );
		head = head->next;
	}
	while(head2->next != NULL)
	{
		fprintf(file, "Rented,%d,%s,%d\n", head2->miles,head2->registration,head2->returnDate );
		head2 = head2->next;
	}
	while(head3->next != NULL)
	{
		fprintf(file, "Repair,%d,%s,%d\n", head3->miles,head3->registration,head3->returnDate );
		head3 = head3->next;
	}
	fclose(file);

	return;
}

int main (int argc, char **argv)
{
	int userChoice = 1;
	int originalMiles = 0;
	int mileage=0;
	int result;
	int totalResult = 0;

	int miles;
	char license[9];
	int date;
	int licenseLength;

	cars* newCar = malloc(sizeof(struct cars));
	cars* newCar2 = malloc(sizeof(struct cars));

	cars* rentedList = malloc(sizeof(struct cars));
	cars* availableList = malloc(sizeof(struct cars));
	cars* repairList = malloc(sizeof(struct cars));

	availableList = readFileAvail(availableList);
	rentedList = readFileRented(rentedList);
	repairList = readFileRepair(repairList);

	while (userChoice != 0) //keep looping until the end
	{	
		totalResult = totalResult + result; //maintains a count of money
		result = 0;//reset count of each returned car

		printf("\n");
		printf("1) Add a new car to the available for rent list\n");
		printf("2) Add a rented car to the available list\n");
		printf("3) Add a rented car to the repair list\n");
		printf("4) Transfer a car from the repair list to the for rent list\n");
		printf("5) Rent the first available car\n");
		printf("6) Print all lists\n");
		printf("7) Quit\n");

		scanf("%d",&userChoice);
		sortMileage(availableList);
		sortReturnDate(rentedList);

		switch(userChoice) {
		case 1:
			printf("Adding new car for rent list\n");
			printf("License plate\n");
			scanf("%s", license);
			licenseLength = strlen(license);
			//check user input for license is correct
			while((licenseLength >7) || (licenseLength <5))
			{
				printf("License plate\n");
				scanf("%s", license);
				licenseLength = strlen(license);
			}

			//check license to make sure no duplicate
			originalMiles = searchOriginalMileage(availableList,license);
			if (originalMiles != 0)
			{
				printf("Sorry same car license found in this list\n");
			}
			else
			{
				//make node and add to available list
				printf("Mileage of car\n");
				scanf("%d", &miles);
				newCar = makeCar(miles,license, 0); 
				availableList = addtoList(availableList,newCar);
			}
		break;
		case 2:
			printf("Add returned car from rented list to available list\n");
			printf("License plate\n");
			scanf("%s", license);
			licenseLength = strlen(license);
			//check user input for license is correct
			while((licenseLength > 8) || (licenseLength < 6))
			{
				printf("License plate\n");
				scanf("%s", license);
				licenseLength = strlen(license);
			}

			originalMiles = searchOriginalMileage(rentedList,license);
			if (originalMiles == 0)
			{
				printf("Not in list\n"); //finish if license searced is not there
			}
			else
			{
				printf("New mileage of car\n");
				scanf("%d", &miles);

				while(originalMiles > miles)
				{
					printf("Returned mileage is less than original\n"); //keep on asking for correct mileage
					printf("New mileage of car\n");
					scanf("%d", &miles);
				}

				printf("Original miles of this car: %d\n", originalMiles );
				removeCar(rentedList,license);//remove from rented list
				mileage = miles-originalMiles;//used to calculate difference
				printf("Mileage difference = %d\n", mileage );
				if (mileage <= 100)
				{
					result = 40;
				}
				else
				{
					mileage = mileage-100;
					result = (int)(mileage*0.15);
					result = result + 40;
				}
				
				printf("Charge for this car: $%d\n", result );
				//move that new car to the available list
				newCar = makeCar(miles,license, 0);
				availableList = addtoList(availableList,newCar);
			}
		break;
		case 3:

			printf("Add returned car from rented list to repair list\n");
			printf("License plate\n");
			scanf("%s", license);
			licenseLength = strlen(license);
			//check user input for license is correct
			while((licenseLength > 8) || (licenseLength < 6))
			{
				printf("License plate\n");
				scanf("%s", license);
				licenseLength = strlen(license);
			}
			originalMiles = searchOriginalMileage(rentedList,license);

			if (originalMiles == 0)
			{
				printf("Not in list\n");
			}
			else
			{
				printf("New mileage of car\n");
				scanf("%d", &miles);
				//makes sure returned miles is greater than the original miles
				while(originalMiles > miles)
				{
					printf("Returned mileage is less than original\n");
					printf("New mileage of car\n");
					scanf("%d", &miles);
				}

				//remove from repair list
				printf("Original miles of this car: %d\n", originalMiles );
				removeCar(rentedList,license);
				mileage = miles-originalMiles;
				printf("Mileage difference = %d\n", mileage );
				mileage = miles-originalMiles;
				if (mileage <= 100)
				{
					result = 40;
				}
				else
				{
					mileage = mileage-100;
					result = (int)(mileage*0.15);
					result = result + 40;
				}
				printf("Charge for this car: $%d\n", result );				
				newCar = makeCar(miles,license, 0); //move that new car to the available list
				repairList = addtoList(repairList,newCar);
			}
		break;
		case 4:
			printf("Transfer\n");
		    printf("License plate\n");
			scanf("%s", license);
			originalMiles = searchOriginalMileage(repairList,license); //grab original miles
			//if returned 0, then it could not be found
			if (originalMiles == 0)
			{
				printf("Not in list\n");
			}
			else
			{
				removeCar(repairList,license); //remove from list
				newCar = makeCar(originalMiles,license,0);//create new node to add to list
				availableList = addtoList(availableList,newCar);
			}
		break;
		case 5:
			printf("Expected return date? (yymmdd)\n");
			scanf("%d", &date); //date has to be 6 digits long

			while((date > 1000000) || (date < 99999))
			{
				printf("Expected return date? (yymmdd)\n");
				scanf("%d", &date);
			}
			//get car from head of availablelist
			newCar = getHead(availableList);
			printf("First car from available list is: %s\n", newCar->registration);
			//make car with new date
			newCar2 = makeCar(newCar->miles,newCar->registration,date);
			//removecar from list
			removeCar(availableList,newCar->registration);
			rentedList = addtoList(rentedList,newCar2);
		break;
		case 6:
			//print each list
			printf("Print available list\n");
			printList(availableList);
			printf("Print rented list\n");
			printList(rentedList);
			printf("Print repair list\n");			
			printList(repairList);
		break;
		case 7:
			printf("Goodbye\n");
			printf("Total Result = $%d\n", totalResult);
			printToFile(availableList,rentedList,repairList);
			return 0;
		break;
		default:
			printf("Wrong input try again\n");
		break;

		}
	}
	return 0;
}
