//Nathan Reymer
//0797359
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node //Oringial data structure title is original
{
    int freq;
    char key[10]; //Should be enough.... pointers were bad.
    struct node*  left;
    struct node*  right;
    int height;
} node;

node* findFreq(int freq, node* t );
node* findKey(char *key, node* t );
node* find_min( node *t );
node* insert(int freq,char *key, node* t );
void print(node* t);
int getBalance(node *n);
node* deleteNode(struct node* root, char * key);
struct node* readFile(char * iFile,node *root);

struct node* readFile(char * iFile,node *root)
{
    node *new,*F;
    new=NULL;
    int count=0;
    FILE *fp;
    fp = fopen(iFile,"r");
    if(fp==NULL)
    {
        printf("no_such_file\n"); //Return an empty AVL Tree
        return NULL;
    }
    char buff[202];
    char* token, *saved;
    int freq;
    char * key;
    while(fgets (buff, 200, fp)!=NULL)  //Read (hopefully) the whole line
    {
        token="";   //Reset just to make sure
        saved="";
        if(buff[strlen(buff)-1]=='\n')  //Trim the fat
        buff[strlen(buff)-1]='\0';

        if (buff[0] == '\n' || buff==NULL)  //Trim more of the fat
        {
            fgets (buff, 200, fp);  //Kill empty lines
            if(buff[strlen(buff)-1]=='\n')
            buff[strlen(buff)-1]='\0';
        }
        for (token = strtok_r(buff, " ", &saved); token; token = strtok_r(NULL, " ", &saved))   //Tokenize the whole thing
        {
            F=findKey(token, new);
            if(F==NULL)     //Check to see if it exits
            {
                new=insert(1,token,new);
            }
            else
            {
                F->freq++;
            }
        }
    }
//    printf("\n");
    //print(new);
    fclose(fp);
    return new;
}

node* find_min( node* t ) //Minimum
{
    if( t == NULL )
    return NULL;
    else if( t->left == NULL )
    return t;
    else
        return find_min( t->left );
}

static int height( node* n ) //Height
{
    if( n == NULL )
    return -1;
    else
        return n->height;
}

static int max( int l, int r) //Was fun to learn ?
{
    return l > r ? l: r;
}

static node* SL( node* k2 ) //Single Left Rotate
{
    node* k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    return k1;
}


static node* SR( node* k1 ) //Single Right Rotate
{
    node* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;

    return k2;
}
static node* LL( node* k3 ) //Double Left Rotate
{
    k3->left = SR( k3->left );
    return SL( k3 );
}
static node* RR( node* k1 ) //Double Right Rotate
{
    k1->right = SL( k1->right );
    return SR( k1 );
}

node* insert(int freq,char *key, node* t ) //The fun part
{
    if( t == NULL ) //Create something outta nothin
    {
        t = (node*)malloc(sizeof(node));
        t->freq = freq;
        strcpy(t->key,key); //Took far too long to figure this out
        t->height = 0;
        t->left = t->right = NULL;
    }
    if(strcmp(t->key,key)<=-1)  //Less than node
    {
        t->left = insert(freq,key,t->left );
        if( height( t->left ) - height( t->right ) == 2 )
        {
            if(strcmp(t->key,key)<=-1) //Rotate!
            {
                t = SL( t );
            }
            else
            {
                t = LL( t );
            }
        }
    }
    else if(strcmp(t->key,key)>=1) //Greater than node
    {
        t->right =insert(freq,key, t->right );
        if( height( t->right ) - height( t->left ) == 2 )
        {
            if(strcmp(t->key,key)>=1) //Rotate!
            {
                t = SR( t );
            }
            else
            {
                t = RR( t );
            }
        }

    }
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
node* findKey(char *key, node* t ) //Returns key (if exists)
{
    if( t == NULL )
    {
    return NULL;}
    if(strcmp(t->key,key)<=-1)  //Less than
    {
        return findKey( key, t->left );
    }
    if(strcmp(t->key,key)>=1)//Greater than
    {
        return findKey( key, t->right );
    }
    if(strcmp(t->key,key)==0){
        return t;
    }
    else
        return t;
}
node* findFreq(int freq, node* t ) //Loops through tree outputting >= freq keys
{
    if( t == NULL )
    return NULL;
    if(t->freq >= freq)
    {
        printf("Key: %s, Frequency: %d\n",t->key,t->freq);
    }
    findFreq(freq,t->left);
    findFreq(freq,t->right);
    return t;
}
void print(node* t) //Just for me really
{
    if (t == NULL)
        return;
    printf("Key: %s, Frequency: %d\n",t->key,t->freq);
    print(t->left);
    print(t->right);
}
int getBalance(node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

node* deleteNode(struct node* root, char * key) //Less of the fun part
{
    if (root == NULL)
        return root;
    if(strcmp(root->key,key)<=-1)
    root->left = deleteNode(root->left, key);

    if(strcmp(root->key,key)>=1)
    root->right = deleteNode(root->right, key);

    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
            if(temp == NULL)
            {
                temp = root;    //Free
                root = NULL;
            }
            else
                *root = *temp;  //Better free
            free(temp);
        }
        else
        {
            node* temp = find_min(root->right); //Start the delete
            strcpy(temp->key,root->key);
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;
    root->height = max(height(root->left), height(root->right)) + 1; //Rotate after delete
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) //Single Right
        return SR(root);
    if (balance > 1 && getBalance(root->left) < 0)  //Single Left, then Single Right
    {
        root->left =  SL(root->left);
        return SR(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)   //Single Left
        return SL(root);
    if (balance < -1 && getBalance(root->right) > 0)    //Single Right then single Left
    {
        root->right = SR(root->right);
        return SL(root);
    }
    return root;
}



int main(int argc, char**argv) {
    char* input=calloc(80,sizeof(char)); //Should be more than enough.
    struct node *AVL, *F;
    AVL = malloc(sizeof(struct node) );
    F=malloc(sizeof(struct node));
    int choice,iInput;
    
    while(choice!=7)    //Start the loop
    {
        printf("1. Initialization \n");
        printf("2. Find \n");
        printf("3. Insert \n");
        printf("4. Remove \n");
        printf("5. Check Height and Size \n");
        printf("6. Find All (above a given frequency) \n");
        printf("7. Exit. \n");
        printf("avl/> ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            printf("Filename: ");
            scanf("%s",input);
            AVL=readFile(input,AVL);
            break;
            case 2:
            printf("Find key: ");
            scanf("%s",input);
            F=findKey(input, AVL);
            if(F==NULL)
            printf("no_such_key\n"); //Ugly phrase, but okay!
            else
                printf("Key: %s, Frequency: %d\n",F->key,F->freq);
            break;
            case 3:
            printf("Insert key: ");
            scanf("%s",input);
            F=findKey(input, AVL);  //insert key or Bump up key freq
            if(F==NULL)
            {
                AVL=insert(1,input,AVL);
            }
            else
            {
                F->freq++;
            }
            F=findKey(input, AVL);
            printf("Key: %s, Frequency: %d\n",F->key,F->freq);
            break;
            case 4:
            printf("Remove key: "); //Same thing as above but reverse
            scanf("%s",input);
            F=findKey(input, AVL);
            if(F==NULL)
            {
                printf("no_such_key\n");
            }
            else if(F->freq>1)
            {
                F->freq--;
            }
            else
            {
                AVL=deleteNode(AVL,input);
            }
            break;
            case 5:
            printf("Height %d Size: ",height(AVL));//Size?
            break;
            case 6:
            printf("Frequency: ");
            scanf("%s",input);
            iInput=atoi(input);
            findFreq(iInput,AVL);
            break;
            case 7:
            break;
            default:
            printf("Not an option \n"); //Please dont loop?
        }

    }
}
