#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct element
{
	char key[20];
	int frequency;
	int height;
	struct element* left;
	struct element* right;
} element;

element* readFile (element* root, char *fileRead);
int max(int left, int right);
int height(element* node);
element* singleLeft(element* node);
element* singleRight(element* node);
element* doubleLeft(element* node);
element* doubleRight(element* node);
element* insert(int frequency,char *key, element* temp);
element* findKey (char* key, element *temp);
int getBalance(element *node);
element* findMin(element* temp ) ;
element* findFrequency(int number, element* temp );
element* deleteNode(struct element* root, char * key);
int sizeTree(element* temp);;

element* readFile (element* root, char *fileRead)
{
	FILE* file;
	char word[255];
	char* token;
	element* found;
	element* theList = NULL;
	int length;
	//file = fopen("1","r");
    file = fopen(fileRead, "r");
	if(file == NULL)
	{
		printf("Could not open file\n");
		return NULL;
	}

	while(fgets(word,255,file) != NULL)
	{
		token = strtok(word, " ");
		while(token != NULL)
		{
			length = strlen(token);
			if (token[length-1] == '\n' )//remove newline replace with null
			{
				token[length-1] = '\0';
			}

			found = findKey(token, theList);  //check the list for the key
			if (found == NULL)
			{
				theList = insert(1,token,theList); //if not found insert into the list
			}
			else
			{
				found->frequency++; //else increase the frequency
			}
			token = strtok(NULL, "\n ");
		}
	}
	fclose(file);
	return theList;
}

int max(int left, int right)
{
    if (left>right)
    {
        return left;
    }
    else
    {
        return right; //checking for maximum left or right node
    }
}

int height(element* node)
{
    if( node == NULL )
    {
    	return -1;
    }
    else
    {
        return node->height;
    }
}

element* singleLeft(element* node) //Single Left Rotate
{
    element* temp = NULL;

    temp = node->left;
    node->left = temp->right;
    temp->right = node;

    node->height = max(height(node->left),height(node->right))+1;
    temp->height = max(height(temp->left),node->height)+1;
    return temp;
}

element* singleRight(element* node) //Single Right Rotate
{
    element* temp = NULL;

    temp = node->right;
    node->right = temp->left;
    temp->left = node;

    node->height = max(height(node->left), height(node->right))+1;
    temp->height = max(height(temp->right),node->height)+1;

    return temp;
}

element* doubleLeft(element* node) //Double Left Rotate
{
    node->left = singleRight(node->left);
    return singleLeft(node);
}

element* doubleRight(element* node) //Double Right Rotate
{
    node->right = singleLeft(node->right);
    return singleRight(node);
}

element* insert(int frequency,char *key, element* temp)
{
    if( temp == NULL ) //check if there is one
    {
        temp = (element*)malloc(sizeof(element));
        temp->frequency = frequency;
        strcpy(temp->key,key); 
        temp->height = 0;
        temp->left = NULL;
        temp->right = NULL;
    }

    if(strcmp(temp->key,key)<0) //if the difference is less than 0
    {
        temp->left = insert(frequency,key,temp->left);
        if( height(temp->left)-height(temp->right)==2) //checking height
        {
            if(strcmp(temp->key,key)>0)
            {
                temp = doubleLeft(temp); //double left rotate
            }
            else
            {
                temp = singleLeft(temp); //single left rotate
            }
        }
    }
    else if(strcmp(temp->key,key)>0) //Greater than node
    {
        temp->right =insert(frequency,key, temp->right ); 
        if( height(temp->right)-height(temp->left)==2) //checking the height before rotation
        {
            if(strcmp(temp->key,key)<0) 
            {
                temp = doubleRight(temp); //double right rotate
            }
            else
            {
                temp = singleRight(temp);//single right rotate
            }
        }

    }
    temp->height = max(height(temp->left),height(temp->right))+1; //keep on checking height
    return temp;
}

element* findKey (char* key, element *temp)
{
    if(temp == NULL)
    {
    	return NULL;
    }
    if(strcmp(temp->key,key)<0)  //Less than
    {
        return findKey( key, temp->left);
    }
    else if(strcmp(temp->key,key)>0)//Greater than
    {
        return findKey( key, temp->right);
    }
    else 
    {
        return temp;
    }
}

int getBalance(element *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return (height(node->left) - height(node->right)); //compare the height of either
    }
}

element* findMin(element* temp) //Minimum
{
    if(temp == NULL)
    {
        return NULL; 
    }
    else if(temp->left == NULL)
    {
        return temp;
    }
    else
    {
        return findMin(temp->left);
    }
}

element* findFrequency(int number, element* temp ) //print if node is greater than frequency
{
    if(temp == NULL)
    {
    	return NULL;
    }
    if(temp->frequency > number)
    {
        printf("Key: %s, Frequency: %d\n",temp->key,temp->frequency);
    }
    findFrequency(number,temp->left);
    findFrequency(number,temp->right);
    return temp;
}

int sizeTree(element* temp) //print size of the tree
{
    int count = 0;
    while(temp != NULL)
    {
        count++;
        temp = temp->left;
    }
    count = pow(2,count);

    return count;
}

element* deleteNode(struct element* root, char* key)
{
    if (root == NULL) //if there is nothing to delete
    {
        return root;
    	
    }
    if(strcmp(root->key,key)<0)
    {
    	root->left = deleteNode(root->left, key); //keep looping until node is found
    }
    else if(strcmp(root->key,key)>0)
    {
    	root->right = deleteNode(root->right, key);
    }
    else
    {
        if((root->right == NULL) || (root->left == NULL))
        {

            struct element *temp = root->left ? root->left : root->right; //terminology from tutorial
            if(temp == NULL)
            {
                temp = root;   
                root = NULL;
            }
            else
            {
                *root = *temp;  
            }
            free(temp); //free the temp
        }
        else //Starting the deletion
        {
            element* temp = findMin(root->right); 
            strcpy(temp->key,root->key);
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
    {
        return root;	
    }
    //After rotate, then delete

    root->height = max(height(root->left), height(root->right)) + 1; 
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) < 0) 
    {
        root->left =  singleLeft(root->left);
        return singleRight(root);
    }
    else
    {
        return singleRight(root);
    }

    if (balance < -1 && getBalance(root->right) > 0)   
    {
        root->right = singleRight(root->right);
        return singleLeft(root);
    }
    else  
    {
        return singleLeft(root);        
    }
    return root;
}

int main(int argc, char const *argv[])
{
	element *theList = malloc(sizeof(struct element));
	element *finding = malloc(sizeof(struct element));
	char input[10];
	int choice = 1;
	int number;

	printf("Simon Ko\n");
	printf("0906762\n");

	while(choice < 7)
	{
		printf("1) Initialization\n");
		printf("2) Find\n");
		printf("3) Insert \n");
		printf("4) Remove\n");
		printf("5) Check height and size\n");
		printf("6) Find all (above a given frequency)\n");
		printf("7) Exit\n");
		printf("avl/> ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
                printf("filename ");
                scanf("%s",input);
				theList = readFile(theList,input);
			break;
			case 2:
				printf("find key: ");
            	scanf("%s",input);
            	finding=findKey(input, theList);
            	if(finding==NULL)
            	{
            		printf("no_such_key\n"); 
            	}
            	else
            	{
                	printf("key: %s, frequency: %d\n",finding->key,finding->frequency);
            	}
			break;
			case 3:
				printf("insert key:\n");
				scanf("%s", input);
				finding = findKey(input,theList);
				if(finding == NULL)
				{
					theList = insert(1,input,theList);

				}
				else
				{
					finding->frequency++;
				}
				finding=findKey(input, theList);
				printf("key: %s frequency: %d\n",input,finding->frequency );
			break;
			case 4:
				printf("remove key ");
				scanf("%s",input);
				finding = findKey(input,theList);
				if(finding == NULL)
				{
					printf("no_such_key\n");
				}
				else if (finding->frequency > 1)
				{
					finding->frequency--;
                    printf("key: %s frequency: %d\n",input, finding->frequency);
				}
				else
				{
					theList = deleteNode(theList,input);
                    printf("deleted key\n");
				}
			break;
			case 5:
				//printf("Height: %d Size: %d\n",height(theList),findMin(theList) );
                //int sizing = sizeTree(0,theList);
				printf("height: %d,size:%d\n",height(theList),sizeTree(theList));
			break;
			case 6:
				printf("frequency: ");
				scanf("%d",&number);
				findFrequency(number,theList);
			break;
			case 7:
				printf("Bye\n");
                return 0;
			break;
			default:
				printf("Wrong input\n");
			break;

		}
	}

	return 0;
}