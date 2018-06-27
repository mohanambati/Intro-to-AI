/********************************************************************************************************************************************************/
// Title: CSCI 8456 Assignment-1                                            
// Written By: Mohan Sai Ambati.
// Program Name: prog2_2.c
// 
// Description:
//	
//  This program initial state in thecommand line in format XXXXXXXXX, 
//  where each X corresponds to a digit between 0 and 8. 
//	The output of the program is printed on two lines 
//		–The first line will print out the goal state as “Goal State is 012345678”. 
//		-In the second line the action sequence, each move separated by a ‘-‘ (e.g., Solution: D-R-D-D) found by algorithm.
//
/********************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************************************************************************************************/
//     Definitions.
/***********************************************************************************************************************************************************/

#define MAX 1000000
#define MAXSIZE 100

/***********************************************************************************************************************************************************/
//	Global variables.
/***********************************************************************************************************************************************************/

int input[3][3];
int count = 0, state,x,y;
int x = 0,y = 0,z = 0,l=0, right = 0, up = 0,key = 0;
int tscore = 999, wcount = 0;
int goal_state1[9]={0,1,2,3,4,5,6,7,8};

/***********************************************************************************************************************************************************/
//     Data Structure.
/***********************************************************************************************************************************************************/

struct queue {

	struct Node* item[MAX];
	int front; //0
	int rear; //-1
	int itemCount;

};

struct stack
{
    char *stk[MAXSIZE];
    int top;
};


struct Node  {
	int fscore;
	int gscore;
	int data[3][3];
	struct Node* parent;
	struct Node* child[3];
};

struct Node *initial_state;




/***********************************************************************************************************************************************************/
//     Check if the initial state is valid or not.
/***********************************************************************************************************************************************************/
int check_state(int state)
{

	int one = 0, two = 0, three = 0, four=0, five=0, zero=0, six = 0, seven = 0, eight = 0;
	int k = 100000000;

for(int i =0; i < 3; i ++)
	for(int j =0; j <3; j++)
{
	input[i][j] = (state/k)%10;
		if(input[i][j] == 1){one++;}
		else if(input[i][j] == 2){two++;}
		else if(input[i][j] == 3){three++;}
		else if(input[i][j] == 4){four++;}
		else if(input[i][j] == 5){five++;}
		else if(input[i][j] == 0){zero++;}
		else if(input[i][j] == 6){six++;}
		else if(input[i][j] == 7){seven++;}
		else if(input[i][j] == 8){eight++;}
	k = k/10;


}

		if(one!=1 || two != 1 || three!= 1 || four != 1 || five != 1 || zero != 1 || six != 1 || seven != 1 || eight != 1)
		{
			printf("Please enter the correct state. \n");
			return 0;
					}
		else return 1;
}

/***********************************************************************************************************************************************************/
//    This function copies one matrix into another.
/***********************************************************************************************************************************************************/

void copy_array(int inputarray[3][3], int output[3][3])
{
	for(int i =0; i < 3; i ++)
	for(int j =0; j <3; j++)
	{
		output[i][j] = inputarray[i][j];
	}
}

/***********************************************************************************************************************************************************/
//     This function prints the state.
/***********************************************************************************************************************************************************/

void print_array(int array[3][3])
{
	for(int i =0; i < 3; i ++)
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

int compare_matrix(int array1[3][3],int array2[3][3])
{
	
	if(array1 == NULL || array2 == NULL) return 1;
	else{

		for(int i =0; i < 3; i ++)
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

int goal_check(int array[3][3])
{

count = 0;
for(int i =0; i < 3; i ++)
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
void find_xy(int array[3][3])
{
 		for(int i =0; i < 3; i ++)
				for(int j =0; j < 3; j++)
				{
					if(array[i][j] == 0)
						{x = i; y = j;}
				}

					if(z == 0) z= x;
			if(l == 0) l = y; 
}

/***********************************************************************************************************************************************************/
//     /* Function to check priority and place element */
/***********************************************************************************************************************************************************/

void check(struct Node* node, struct queue* set)
{
    int i,j;
 
    for (i = 0; i <= set->rear; i++)
    {
        if (node->fscore >= set->item[i]->fscore)
        {
            for (j = set->rear + 1; j > i; j--)
            {
                set->item[j] = set->item[j - 1];
            }
            set->item[i] = node;
            return;
        }
    }
    set->item[i] = node;
}

/***********************************************************************************************************************************************************/
//     /* Function to insert an element in the priority queue.*/
/***********************************************************************************************************************************************************/

void insert(struct Node* node, struct queue* set)
{
    if (set->rear >= MAX - 1)
    {
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((set->front == -1) && (set->rear == -1))
    {
        set->front++;
        set->rear++;
        set->itemCount++;
        set->item[set->rear] = node;
        return;
    }    
    else
        check(node,set);
    set->rear++;
    set->itemCount++;
}
 
/***********************************************************************************************************************************************************/
//     /* Function to remove an element from the priority queue. */
/***********************************************************************************************************************************************************/
void removeData(struct Node* node,struct queue* set)
{
    int i;
 
    if ((set->front==-1) && (set->rear==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return;
    }
 
    for (i = 0; i <= set->rear; i++)
    {
        if (compare_matrix(node->data,set->item[i]->data))
        {
            for (; i < set->rear; i++)
            {
                set->item[i] = set->item[i + 1];
            }
 
        set->item[i] = NULL;
        set->rear--;
        set->itemCount--;
 
        if (set->rear == -1) 
            set->front = -1;
        return;
        }
    }
    printf("\n not found in queue to delete");
}

/***********************************************************************************************************************************************************/
//     /* Function to check if the queue is empty or not. */
/***********************************************************************************************************************************************************/

int isEmpty(struct queue* set)
{
	  if ((set->front==-1) && (set->rear==-1)) return 1;
	  return 0;

}

/***********************************************************************************************************************************************************/
//     /* Function to get the position of each digit in a matrix to find the manhattan distance.*/
/***********************************************************************************************************************************************************/

int get_position(struct Node* node,int k)
{
	x = 0, y = 0;
	
	for(int i =0; i < 3; i ++)
				for(int j =0; j < 3; j++)
				{
					if(node->data[i][j] == k)
						{x = i; y = j;}
				}


	//printf("x,y : %d,%d\n",x,y );

	if(x==0&&y==0) return 0;
	else if(x==0&&y==1) return 1;
	else if(x==0&&y==2) return 2;
	else if(x==1&&y==0) return 3;
	else if(x==1&&y==1) return 4;
	else if(x==1&&y==2) return 5;
	else if(x==2&&y==0) return 6;
	else if(x==2&&y==1) return 7;
	else if(x==2&&y==2) return 8;
}

/***********************************************************************************************************************************************************/
//     /* Function calicualtes the manhattan distance. */
/***********************************************************************************************************************************************************/

int heuristic_cost_estimate(struct Node* node)
{
	int manhatten = 0;
		int references[9][9] ={

		//////*0 1 2 3 4 5 6 7 8*//////
		/*0*/{ 0,1,2,1,2,3,2,3,4 }/*0*/,
		/*1*/{ 1,0,1,2,1,2,3,2,3 }/*1*/,
		/*2*/{ 2,1,0,3,2,1,4,3,2 }/*2*/,
		/*3*/{ 1,2,3,0,1,2,1,2,3 }/*3*/,
		/*4*/{ 2,1,2,1,0,1,2,1,2 }/*4*/,
		/*5*/{ 3,2,1,2,1,0,3,2,1 }/*5*/,
		/*6*/{ 2,3,4,1,2,3,0,1,2 }/*6*/,
		/*7*/{ 3,2,3,2,1,2,1,0,1 }/*7*/,
		/*8*/{ 4,3,2,3,2,1,2,1,0 }/*8*/
		//////*0 1 2 3 4 5 6 7 8*//////
		};

		for(int i = 0;i < 9; i++)
			manhatten += references[i][get_position(node,i)];
		//printf("manhatten = %d\n", manhatten );
	return manhatten;

}

/***********************************************************************************************************************************************************/
//     /* Function to get the least heuristic value in queue*/
/***********************************************************************************************************************************************************/

struct Node* get_leastfscore(struct queue* set)
{
	int score = 0,key = 0;
	score = set->item[0]->fscore;
	//printf("score copied. \n");
	
	for( int i =0; i < set->itemCount; i++)
	{
		//printf("in loop i: %d \n",i);
		
		if(set->item[i]->fscore < score && set->item[i] != NULL)
			{score = set->item[i]->fscore;
				key = i;
			//	printf("in loop key: %d \n",key);
			}
	}

//	printf("before return. \n");

	return set->item[key];
}

/***********************************************************************************************************************************************************/
//     /* Function to compare heuristic cost. /
/***********************************************************************************************************************************************************/

int fscore_compare(struct Node* node,struct queue* set,struct queue* cset)	
{

	for (int i = 0; i < set->itemCount; ++i)
	{
		if(compare_matrix(set->item[i]->data, node->data))
		{
			if(set->item[i]->fscore >= node->fscore) {return 1;}
			 else return 0;
			
		}
		
	}


	for(int i = 0; i < cset->itemCount; ++i)
		if(compare_matrix(cset->item[i]->data, node->data)) return 0;



	return 1;
}

/***********************************************************************************************************************************************************/
//     Succesor function genrates the child nodes and adds it to root node.
/***********************************************************************************************************************************************************/
void successor_gen(struct Node* node, struct queue* openset, struct queue* closeset)
{	int temp,fscore;
	struct Node* order = (struct Node*) malloc(sizeof(struct Node));
		struct Node* left = (struct Node*) malloc(sizeof(struct Node));
			struct Node* right = (struct Node*) malloc(sizeof(struct Node));
			struct Node* up = (struct Node*) malloc(sizeof(struct Node));
				struct Node* down = (struct Node*) malloc(sizeof(struct Node));
				int l=0,r=0,u=0,d=0;
	// move left
x = 0; y =0; z = 0; l = 0;
	find_xy(node->data);

	if(x == z && y > 0){
	
	copy_array(node->data,left->data);

	        temp = left->data[x][y];
			left->data[x][y] = left->data[x][y-1];
			left->data[x][y-1] = temp;

			if(node->parent != NULL){
		if(!compare_matrix(node->parent->data, left->data)  && !compare_matrix(node->data,left->data) && fscore_compare(left,openset,closeset))
			{
			  node->child[0] = left;left->parent = node;
			  	fscore = heuristic_cost_estimate(left);
				l = 1;
				insert(left,openset);
				left->gscore = node->gscore + 1;
				left->fscore = fscore+left->gscore;

			}}
		else {
		  node->child[0] = left;left->parent = node;
		  fscore = heuristic_cost_estimate(left);
				l = 1;
				insert(left,openset);
				left->gscore = node->gscore + 1;
				left->fscore = fscore+left->gscore;
		}


		}



x = 0; y =0; z = 0; l = 0;
find_xy(node->data);

if(x == z && y <2 ){


	copy_array(node->data,right->data);


	temp = right->data[x][y];
			right->data[x][y] = right->data[x][y+1];
			right->data[x][y+1] = temp;

	

		if(node->parent != NULL){ 
		if(!compare_matrix(node->parent->data, right->data) &&!compare_matrix(node->data,right->data) && !compare_matrix(left->data, right->data) && fscore_compare(right,openset,closeset))	
			{
				node->child[1] = right;
	right->parent = node;
	fscore = heuristic_cost_estimate(right);
				r=1;
				insert(right,openset);
				right->gscore = node->gscore + 1;
				right->fscore = fscore+right->gscore;
	} }
		else {
			node->child[1] = right;
	right->parent = node;
	fscore = heuristic_cost_estimate(right);
				r=1;
				insert(right,openset);
				right->gscore = node->gscore + 1;
				right->fscore = fscore+right->gscore;
		}

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
		if(!compare_matrix(node->parent->data, up->data) &&!compare_matrix(node->data,up->data) && !compare_matrix(up->data, right->data) && !compare_matrix(left->data, up->data)&& fscore_compare(up,openset,closeset))	
			{
				node->child[2] = up;
	up->parent = node;
fscore = heuristic_cost_estimate(up);
				u = 1;
				insert(up,openset);
				up->gscore = node->gscore + 1;
				up->fscore = fscore+up->gscore;

	}}
		else {
		 	node->child[2] = up;
	up->parent = node; 
fscore = heuristic_cost_estimate(up);
				u = 1;
				insert(up,openset);
				up->gscore = node->gscore + 1;
				up->fscore = fscore+up->gscore;

	}

}

	//move down
x = 0; y =0; z = 0; l = 0;
find_xy(node->data);
if(x < 2){


	copy_array(node->data,down->data);


	temp = down->data[x][y];
			down->data[x][y] = down->data[x+1][y];
			down->data[x+1][y] = temp;

			if(node->parent != NULL){

		if(!compare_matrix(node->parent->data, down->data) &&!compare_matrix(node->data,down->data) && !compare_matrix(down->data, right->data) && !compare_matrix(left->data, down->data)  && fscore_compare(down,openset,closeset) && !compare_matrix(up->data, down->data))
			{
			  node->child[3] = down;
	         down->parent = node;
	
	         fscore = heuristic_cost_estimate(down);
				d=1;
				insert(down,openset);

				down->gscore = node->gscore + 1;
				down->fscore = fscore+down->gscore;

		}}
		else {
		 		node->child[3] = down;
	             down->parent = node;

				fscore = heuristic_cost_estimate(down);

				insert(down,openset);
				d=1;
				down->gscore = node->gscore + 1;
				down->fscore = fscore+down->gscore;
		}



}


}


/***********************************************************************************************************************************************************/
//     This function perform A* Algoritham.
/***********************************************************************************************************************************************************/
struct Node* Astar(struct Node* node)
{
	int score = 0;
	struct Node* found = (struct Node*) malloc(sizeof(struct Node));
	struct Node* xchange = (struct Node*) malloc(sizeof(struct Node));
	struct queue* openset = (struct queue*) malloc(sizeof(struct queue));
	openset->front = -1;
	openset->rear = -1;
	openset->itemCount = 0;
	struct queue* closeset = (struct queue*) malloc(sizeof(struct queue));
	closeset->front = -1;
	closeset->rear = -1;
	closeset->itemCount = 0;
	
	
	tscore = heuristic_cost_estimate(node);
	node->fscore = tscore;
	node->gscore = 0;
	insert(node,openset);
		//printf("Program will take some time to check maximum depth. \n");
	//printf("Please wait..\n \n");
	
	while(!isEmpty(openset))
	{
		found = get_leastfscore(openset);
			tscore = found->fscore;
			score = found->gscore;

	if(goal_check(found->data)){ 
	//	printf("goal found. \n"); 
		printf("Depth: %d\n",found->gscore);
		printf("Total heuristic : %d \n", found->fscore);
		return found;}
	successor_gen(found,openset,closeset);
	removeData(found,openset);
	insert(found,closeset);

	wcount++;
	}

return NULL;

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
//     This function finds the path of goal state.
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
	for(int i = 0; i <9 ; i++)
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

//printf("state : %d \n",state);

 printgoalstate();

if(check_state(state))
{

if(!ispuzzle_solvable(input)) {printf("Puzzle cannot be solved.\n"); return 0;}
//printf("Puzzle can be solved. \n \n");

initial_state = (struct Node*) malloc(sizeof(struct Node));
initial_state->parent = NULL;
copy_array(input,initial_state->data);

struct Node* found = (struct Node*) malloc(sizeof(struct Node));
found = Astar(initial_state);

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

