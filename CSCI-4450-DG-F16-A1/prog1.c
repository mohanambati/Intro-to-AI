/********************************************************************************************************************************************************/
// Title: CSCI 8456 Assignment-1                                            
// Written By: Mohan Sai Ambati.
// Program Name: prog1.c
// 
// Description:
//	
//  This program prompts the user to enter an initial state in the format XXXXXX, 
//  where each X corresponds to a digit between 0 and 5; e.g., 431502 (no spaces between digits). 
//	The output of the program is printed on two lines 
//		–The first line should print out the goal state as “Goal State is 123450”. 
//		-The second line the action sequence, each move separated by a ‘-‘ (e.g., Solution: D-R-D-D) found by your algorithm.
//
/********************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************************************************************************************************************/
//     Definitions.
/***********************************************************************************************************************************************************/
#define MAXSIZE 1000
#define DEPTH 40
/***********************************************************************************************************************************************************/
//	Global variables.
/***********************************************************************************************************************************************************/

int input[2][3];
int count = 0, state,x,y;
int x = 0,y = 0,z = 0,l=0, right = 0, up = 0;
int goal_state1[6]={1,2,3,4,5,0};

/***********************************************************************************************************************************************************/
//     Data Structure.
/***********************************************************************************************************************************************************/
struct stack
{
    char *stk[MAXSIZE];
    int top;
};

struct Node  {
	int data[2][3];
	int depth;
	struct Node* parent;
	struct Node* child[3];
};

struct Node *initial_state;

/***********************************************************************************************************************************************************/
//     Check if the initial state is valid or not.
/***********************************************************************************************************************************************************/
int check_state(int state)
{

	int one = 0, two = 0, three = 0, four=0, five=0, zero=0;
	int k = 100000;

for(int i =0; i < 2; i ++)
	for(int j =0; j <3; j++)
{
	input[i][j] = (state/k)%10;
		if(input[i][j] == 1){one++;}
		else if(input[i][j] == 2){two++;}
		else if(input[i][j] == 3){three++;}
		else if(input[i][j] == 4){four++;}
		else if(input[i][j] == 5){five++;}
		else if(input[i][j] == 0){zero++;}
	k = k/10;


}

		if(one!=1 || two != 1 || three!= 1 || four != 1 || five != 1 || zero != 1)
		{
			printf("Please enter the correct state. \n");
			return 0;
					}
		else return 1;
}

/***********************************************************************************************************************************************************/
//    This function copies one matrix into another.
/***********************************************************************************************************************************************************/

void copy_array(int inputarray[2][3], int output[2][3])
{
	for(int i =0; i < 2; i ++)
	for(int j =0; j <3; j++)
	{
		output[i][j] = inputarray[i][j];
	}
}

/***********************************************************************************************************************************************************/
//     This function prints the state.
/***********************************************************************************************************************************************************/

void print_array(int array[2][3])
{
	for(int i =0; i < 2; i ++)
	{for(int j =0; j <3; j++)
	{
		printf("%d",array[i][j]);
	}
	printf("\n");
	}
}

/***********************************************************************************************************************************************************/
//   This function compares two matrices and check if they are equal or not.
/***********************************************************************************************************************************************************/

int compare_matrix(int array1[2][3],int array2[2][3])
{
	
	if(array1 == NULL || array2 == NULL) return 1;
	else{

		for(int i =0; i < 2; i ++)
		for(int j =0; j <3; j++)
			if(array1[i][j] != array2[i][j])
			{
				return 0;
			}

			return 1;}

}

/***********************************************************************************************************************************************************/
//    This function check if the state is goal state or not.
/***********************************************************************************************************************************************************/

int goal_check(int array[2][3])
{

count = 0;
for(int i =0; i < 2; i ++)
	for(int j =0; j <3; j++)
	{
		if(array[i][j] != goal_state1[count])
		 return 0;
	count++;
	}
	return 1;
}

/***********************************************************************************************************************************************************/
//     This function will search for "0" position in given state.
/***********************************************************************************************************************************************************/
void find_xy(int array[2][3])
{
 		for(int i =0; i < 2; i ++)
				for(int j =0; j < 3; j++)
				{
					if(array[i][j] == 0)
						{x = i; y = j;}
				}

					if(z == 0) z= x;
			if(l == 0) l = y; 
}

/***********************************************************************************************************************************************************/
//     This function pushes an element to stack.
/***********************************************************************************************************************************************************/

int push(struct stack* track,char *direction)
{
	 char *num;
    if (track->top == (MAXSIZE - 1))
    {
        printf ("stack is Full\n");
        return 0;
    }
    else
    {
        track->top = track->top + 1;
        track->stk[track->top] = direction;
     }
    return 1;
}

/***********************************************************************************************************************************************************/
//  This function pops an element from stack.
/***********************************************************************************************************************************************************/

char* pop (struct stack* track)
{
	char *direction;
    
    if (track->top == - 1)
    {
        printf ("Stack is Empty\n");
        return NULL;
    }
    else
    {
    	  direction = track->stk[track->top];
        track->top = track->top - 1;
    }
    return direction;
}

/***********************************************************************************************************************************************************/
//     This function checks if stack is empty or not.
/***********************************************************************************************************************************************************/

int stack_isempty(struct stack* track)
{
	 if (track->top == - 1) return 1;
	 else return 0;

}

/***********************************************************************************************************************************************************/
//     Succesor function genrates the child nodes and adds it to root node.
/***********************************************************************************************************************************************************/
void successor_gen(struct Node* node)
{	int temp;
		struct Node* left = (struct Node*) malloc(sizeof(struct Node));
			struct Node* right = (struct Node*) malloc(sizeof(struct Node));
			struct Node* up = (struct Node*) malloc(sizeof(struct Node));
	// move left
x = 0; y =0; z = 0; l = 0;
	find_xy(node->data);

	if(x == z && y > 0){
	
	copy_array(node->data,left->data);

	        temp = left->data[x][y];
			left->data[x][y] = left->data[x][y-1];
			left->data[x][y-1] = temp;

			if(node->parent != NULL){
		if(!compare_matrix(node->parent->data, left->data)  &&!compare_matrix(node->data,left->data))	
			{//push(fringe,left);
			  node->child[0] = left;left->parent = node;}}
		else {//push(fringe,left);
		  node->child[0] = left;left->parent = node;}
		//if(!compare_parent(left,fringe)) push(fringe,left);

		}

x = 0; y =0; z = 0; l = 0;
find_xy(node->data);

if(x == z && y <2 ){


	copy_array(node->data,right->data);


	temp = right->data[x][y];
			right->data[x][y] = right->data[x][y+1];
			right->data[x][y+1] = temp;

	

		if(node->parent != NULL){ 
		if(!compare_matrix(node->parent->data, right->data) &&!compare_matrix(node->data,right->data) && !compare_matrix(left->data, right->data) )	
			{//push(fringe,right); 
				node->child[1] = right;
	right->parent = node;
	} }
		else {//push(fringe,right);
			node->child[1] = right;
	right->parent = node;}

}
	//move up
x = 0; y =0; z = 0; l = 0;
find_xy(node->data);

if(x > 0){

	copy_array(node->data,up->data);


	temp = up->data[x][y];
			up->data[x][y] = up->data[x-1][y];
			up->data[x-1][y] = temp;

if(node->parent != NULL){
		if(!compare_matrix(node->parent->data, up->data) &&!compare_matrix(node->data,up->data) && !compare_matrix(up->data, right->data) && !compare_matrix(left->data, up->data))	
			{//push(fringe,up); 
				node->child[2] = up;
	up->parent = node;}}
		else {//push(fringe,up);
		 	node->child[2] = up;
	up->parent = node; }

}

	//move down
x = 0; y =0; z = 0; l = 0;
find_xy(node->data);
if(x < 1){
	struct Node* down = (struct Node*) malloc(sizeof(struct Node));

	copy_array(node->data,down->data);

	temp = down->data[x][y];
			down->data[x][y] = down->data[x+1][y];
			down->data[x+1][y] = temp;

			if(node->parent != NULL){
		if(!compare_matrix(node->parent->data, down->data) &&!compare_matrix(node->data,down->data) && !compare_matrix(down->data, right->data) && !compare_matrix(left->data, down->data) && !compare_matrix(up->data, down->data))
			{//push(fringe,down);
			 node->child[3] = down;
	down->parent = node;}}
		else {//push(fringe,down);
		 	node->child[3] = down;
	down->parent = node;}
				//if(!compare_parent(down,fringe)) push(fringe,down);
}
}


/***********************************************************************************************************************************************************/
//     Depth Limited Search function.
/***********************************************************************************************************************************************************/
struct Node* DLS(struct Node* node,int depth)
{
	struct Node* found = (struct Node*) malloc(sizeof(struct Node));
	
	
	if(node != NULL && goal_check(node->data)) { return node; }


	if(depth == 0 && goal_check(node->data)){return node;}
	else if(depth > 0)
	{

		successor_gen(node);

		for(int i =0; i < 4; i ++)
		{
			if(node->child[i] != NULL)
			{
				found = node->child[i];
				found = DLS(found,depth-1);
				if(found != NULL && goal_check(found->data)) {return found; }
			}
			if(node == NULL) return NULL;
		}
	}
}

/***********************************************************************************************************************************************************/
//     Iterative Depth Deepining search function.
/***********************************************************************************************************************************************************/

struct Node* IDDFS(struct Node* root, int depth)
{

	struct Node *found = (struct Node*) malloc(sizeof(struct Node));

	for(int i = 0; i <= depth ; i++)
	{	
		found = DLS(root,i);
		
		if(found != NULL && goal_check(found->data)){ printf("depth : %d \n", i); //printf("Goal found. \n \n"); 
		return found;}
	  
	}

	if(found == NULL) return found;


}

/***********************************************************************************************************************************************************/
//     This function prints the action sequence.
/***********************************************************************************************************************************************************/

void print_resultpath(struct Node* node)
{
	int x1,x2,y1,y2;
	char *dir;
	x = 0; y = 0;
struct stack* track = (struct stack*) malloc(sizeof(struct stack));


	while(node!=NULL && node->parent != NULL)
	{
		find_xy(node->data);
	       x1 = x; y1 = y;
	       x = 0; y= 0;
	      find_xy(node->parent->data);
	       x2=x; y2 = y;
	       x = 0; y =0;

	      if(x1 == x2 && y1 > y2) 
	       	{
	       		dir = (char*)'L';
	       		push(track,dir);
	   		}
	   	else if(x1 == x2 && y1 < y2) 
	       	{
	       		dir = (char*)'R';
	       		push(track,dir);
	   		}
	   	else if(x1 < x2 && y1 == y2) 
	       	{
	       		dir = (char*)'D';
	       		push(track,dir);
	   		}
	   	 else if(x1 > x2 && y1 == y2) 
	       	{
	       		dir = (char*)'U';
	       		push(track,dir);
	   		}

		node = node->parent;
	
	}

	if (!stack_isempty(track))
	{
		printf("Action sequence: \n");
	}

	while(!stack_isempty(track))
	{
		dir = pop(track);
		if(dir !=NULL)
		{printf("%c - ",dir);
		}

	}
	printf("\n");

}


/***********************************************************************************************************************************************************/
//    This function checks number of inversions in input state and if no of inversion is even then puzzle is solvable else not solvable.
/***********************************************************************************************************************************************************/

int ispuzzle_solvable(int array[3][3])
{
	int inversions = 0, test[9];

	for(int i =0; i < 3; i ++)
	for(int j =0; j <3; j++)
		{ test[count] = array[i][j];			
		count++;}

	for(int i = 0; i < 9 ; i++)
		for(int j = i + 1; j < 9 ; j++)
			if(test[i] > test[j] && test[j] !=0 )
				inversions++;

	if(inversions%2 == 0) return 1;
		else return 0;
}

/***********************************************************************************************************************************************************/
//    This function just Prints the goal state.
/***********************************************************************************************************************************************************/

void printgoalstate()
{
	printf("Goal State : ");
	for(int i = 0; i <6 ; i++)
	printf("%d", goal_state1[i]);
	printf("\n");

}

/***********************************************************************************************************************************************************/
//    Main function.
/***********************************************************************************************************************************************************/

int main(int argc, char *argv[])
{

 if (argc != 2) {
        printf("Usage: \"%s <input state>\"\n", argv[0]);
        return -1;
    }
state = atoi(argv[1]);

//printf("Input state : %d \n",state);

printgoalstate();

if(check_state(state))
{ 
if(!ispuzzle_solvable(input)) {printf("Puzzle cannot be solved.\n"); return 0;}
//printf("Puzzle can be solved. \n \n");


initial_state = (struct Node*) malloc(sizeof(struct Node));
initial_state->depth = 0;
initial_state->parent = NULL;
copy_array(input,initial_state->data);

struct Node* found = (struct Node*) malloc(sizeof(struct Node));
found = IDDFS(initial_state,DEPTH);

if(found != NULL) 
{
print_resultpath(found);
}
else
	printf("Goal state Cannot be found. \n");

}
else
	printf("input state is wrong. \n");

		return 0;

	}

