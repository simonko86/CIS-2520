/**************************
*Simon Ko 0906762
*Due: 11/7/2016
*Completed: 11/04/2016
*Program that reads an f.dat file
*It parses each line and adds the end of each line
*to the back of the array.  This child compares with
*the parent in the array and checks to see which is 
*smaller If the child is smaller than the parent, the
*key and information switch. This happens until the 
*child is larger than the parent or the child
*is the root.
**************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	FILE *file;
	file = fopen("f.dat", "r");
	int array[20][10] = {0};
	int sum, sum2;
	int tempArray[10] = {0};
	int key = 0;
	int parent;
	int child;

	for (int j = 0; j < 20; ++j) //scanning each line
	{

		for (int i = 0; i < 10; ++i) //scanning each element in the line
		{
				fscanf(file, "%d", &array[j][i]);
		}

			child = j; //child is the line that is being inserted
			parent = (int)child/2; //parent is the child/2

			sum2 = array[child][0]+array[child][1]+array[child][2]; //key of added element
			sum = array[parent][0]+array[parent][1]+array[parent][2]; //key of parent

			//j is current node
			while (sum2 < sum) //while added element < parent
			{
				//swap parent and current node
				for (int k = 0; k < 10; ++k) //perform swap of both key and information
				{
					tempArray[k] = array[parent][k];
					array[parent][k] = array[child][k];
					array[child][k] = tempArray[k];
				}

				child = parent;
				parent = (int)child/2; //find parent
				sum2 = array[child][0]+array[child][1]+array[child][2];
				sum = array[parent][0]+array[parent][1]+array[parent][2]; //key of parent
			}
	}





	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (i<2)
			{
				key = array[j][i] + key;
			}
			else if (i==2)
			{
				key = array[j][i] + key;
				printf("Key: %d  Information: ",key ); //print key total
			}
			else
			{
				printf("%d ", array[j][i]); //print information
			}
		}
		key = 0;
		printf("\n");
	}




	fclose(file);


	return 0;
}
