/********************************************************************************************************************************************************/
// Title: CSCI 8456 Assignment-4                                           
// Written By: Mohan Sai Ambati.
// Program Name: prog2.c
// 
// Description:
//	This program implements the Markov Decision Process value iteration and policy iteration algorithms to plan find optimal policy under uncertanity.
//	This program accepts reward(r) value from the user
/********************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define theta 0.00

float utility[9] = {0.0f};
float prevutility[9];
int actions[4], np = 0;
float r = 0;
float gama = 0.99f ;
int var = 0;
int states[9] = {0,1,2,3,4,5,6,7,8};
float value[9], error =0.0f;
	int tab[9][4] = {

		{3,0,1,0},
		{4,1,2,0},
		{5,2,2,1},
		{6,0,4,3},
		{7,1,5,3},
		{8,2,5,4},
		{6,3,7,6},
		{7,4,8,6},
		{8,5,8,7}
	};

	int route[8][1];
	char policy[8];
	int rewards[8];
	char policy_it[8];
/***********************************************************************************************************************************************************/
//    This function that initialites the utility.
/***********************************************************************************************************************************************************/

void init_environment()
{
	for(int i =0; i<=8 ; i++)
			{utility[i] = 0.0f;
			rewards[i] = -1;
			}

			rewards[8] = +10.0f;
			rewards[6] = r;

}
/***********************************************************************************************************************************************************/
//    This function that generates possible actions.
/***********************************************************************************************************************************************************/
int actionspossible(int state)
{
	if(state == 0) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 1) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 2) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 3) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 4) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 5) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 6) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 7) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
	if(state == 8) {actions[0]=1;actions[1]=1;actions[2]=1;actions[3]=1;}
}

/***********************************************************************************************************************************************************/
//    This function that caliculates maximum rewarded action.
/***********************************************************************************************************************************************************/
float caliculatemaxaction(int state)
{ 	var = 0;
	float max ;
	float re = 0.0f;
	re = utility[state]/10;

	//if( state == 8) {policy[state] = '*'; return utility[state];}

	//printf("%d\n",state );
	for (int i = 0; i < 3; i++)
		actions[i] = 0;

	float val[4] = {0.0f};
	actionspossible(state);
	int moveup = 0, movedown = 0,moveright = 0,moveleft = 0;
	
	if(actions[0] == 1){moveup = 1;}
	if(actions[1] == 1) movedown =1;
	if(actions[2] == 1) moveright = 1;
	if(actions[3] == 1) moveleft = 1;

	if(moveup) val[0]= gama*(0.8*utility[tab[state][0]] + 0.1*utility[tab[state][2]]+ 0.1*utility[tab[state][3]]);
	if(movedown) val[1]= gama*(0.8*utility[tab[state][1]] + 0.1*utility[tab[state][2]] + 0.1*utility[tab[state][3]]);
	if(moveright) val[2]= gama*(0.8*utility[tab[state][2]] + 0.1*utility[tab[state][0]] + 0.1*utility[tab[state][1]]);
	if(moveleft) val[3]= gama*(0.8*utility[tab[state][3]]+ 0.1*utility[tab[state][0]]+ 0.1*utility[tab[state][1]]);



	max= val[0];
	for(int i = 0; i <= 3; i++)
	{
		//printf("%f \n", val[i] );
		if( max < val[i]) {max = val[i]; var = i; }
	}
	
	if(var == 0) policy[state] = 'U';
	else if(var == 1) policy[state] = 'D';
	else if(var == 2) policy[state] = 'R';
	else if(var == 3) policy[state] = 'L';

	return max;

	}
/***********************************************************************************************************************************************************/
//    This function checks if the error is less and model is ready or not.
/***********************************************************************************************************************************************************/

int cooldown(float util1[9], float util2[9])
{
	 error = util1[0] - util2[0];
	 //printf("error : %f\n",error );
	 if(error < 0.001 && error > -0.0001) return 1;

	 return 0;

}



/***********************************************************************************************************************************************************/
//    This function that excutes valu iteration algorithm.
/***********************************************************************************************************************************************************/
void valueiteration()
{
	int stop = 0, count =0;

	//for(int i = 0; i <= 8; i++) printf("rewards[%d]: %d",i,rewards[i]);


	while(!stop){

	//for(int i = 0; i <= 8; i++) printf("utility[%d]: %f",i,utility[i]);

	//	printf("\n");

		for(int i =0 ; i <= 8; i++)	
		prevutility[i] = utility[i];


	for(int i =0; i <= 8; i++){
		if(i == 6) utility[states[i]] =  caliculatemaxaction(states[i]) +  r;
		else if(i == 8 ) utility[states[i]] =  caliculatemaxaction(states[i]) + 10 ;
		else utility[states[i]] =  caliculatemaxaction(states[i]) + rewards[i];

	//printf("max action val at state[%d]: %f/n",states[i],caliculatemaxaction(states[i]));
	//printf("utility : %f \n", utility[states[i]]);
	//for(int i = 0; i <= 10000000; i++){}
	}
	if(utility[0] - prevutility[0] == 0  && count > 20 && utility[1] - prevutility[1] == 0) stop = 1;
	if(count > 1000) stop = 1;

	count ++;
	}


	float max= utility[0];
	int var = 0;
	for(int i = 0; i <= 8; i++)
	{
		//printf("%f \n", val[i] );
		if( max < utility[i]) {max = utility[i]; var = i; }
	}


/*printf("\n%f \t %f \t %f\n",utility[6],utility[7],utility[8] );
printf("%f \t %f \t %f\n",utility[3],utility[4],utility[5] );
printf("%f \t %f \t %f\n\n",utility[0],utility[1],utility[2] );
*/



int a;
	for(int i =0; i<3; i++)
		for(int j = 0; j < 3; j++)
		{printf("(%d,%d) :",j,i);
		if(i == 0) a = i + j;
		if( i == 1) a =i+j+2;
		if( i == 2) a =i+j+4;
		if(a == np) printf("*");
		else printf("%c",policy[a]);
		printf("\n");
		}

}

/***********************************************************************************************************************************************************/
//    This function finds the utility of the state for that policy.
/***********************************************************************************************************************************************************/

float policy_evaluation(int state, char policy)
{
	int moveup = 0, movedown = 0,moveright = 0,moveleft = 0;
	float val = 0.0f;
	if(policy == 'u') moveup = 1;
	else if(policy == 'd') movedown = 1;
	else if(policy == 'r') moveright = 1;
	else if(policy = 'l') moveleft = 1;

	if(moveup) val= gama*(0.8*utility[tab[state][0]] + 0.1*utility[tab[state][2]]+ 0.1*utility[tab[state][3]]);
	if(movedown) val= gama*(0.8*utility[tab[state][1]] + 0.1*utility[tab[state][2]] + 0.1*utility[tab[state][3]]);
	if(moveright) val= gama*(0.8*utility[tab[state][2]] + 0.1*utility[tab[state][0]] + 0.1*utility[tab[state][1]]);
	if(moveleft) val= gama*(0.8*utility[tab[state][3]]+ 0.1*utility[tab[state][0]]+ 0.1*utility[tab[state][1]]);

	return val;

}


/***********************************************************************************************************************************************************/
//    This is the policy iteration function that caliculate sthe optimal policy.
/***********************************************************************************************************************************************************/

void policyiteration()
{
float temputil[8] = {0.0f};
float calutil = 0.0f;
int stop = 0, count = 0;
	//given a policy of the state caliculate the utility.
	//if caliculated utility is greater than any other possible policy reward, re caliculate the reward by taking the maximum rewarded action
while(!stop){

		for(int i =0 ; i <= 8; i++)	
		prevutility[i] = utility[i];

for(int i =0; i <=8 ; i++){
	calutil= policy_evaluation(states[i],policy_it[states[i]]);

if(i == 6) utility[states[i]] = caliculatemaxaction(states[i]) + r;
else if(i == 8) utility[states[i]]= caliculatemaxaction(states[i])+10 ;
else utility[states[i]] = caliculatemaxaction(states[i]) + rewards[i];

	if(utility[0] - prevutility[0] == 0  && count > 20 && utility[1] - prevutility[1] == 0) stop = 1;

	if(count > 1000) stop = 1;
}

count++;

}


float max= utility[0];
	int var = 0;
	for(int i = 0; i <= 8; i++)
	{
		//printf("%f \n", val[i] );
		if( max < utility[i]) {max = utility[i]; var = i; }
	}


/*printf("\n%f \t %f \t %f\n",utility[6],utility[7],utility[8] );
printf("%f \t %f \t %f\n",utility[3],utility[4],utility[5] );
printf("%f \t %f \t %f\n\n",utility[0],utility[1],utility[2] );
*/



int a;
	for(int i =0; i<3; i++)
		for(int j = 0; j < 3; j++)
		{printf("(%d,%d) :",j,i);
		if(i == 0) a = i + j;
		if( i == 1) a =i+j+2;
		if( i == 2) a =i+j+4;
		if(np != a)printf("%c",policy[a]);
		else printf("*");

		printf("\n");
		}


	return;
}
/***********************************************************************************************************************************************************/
//    The main function that.
/***********************************************************************************************************************************************************/
int main()
{
	
int decision;
printf("Enter r:");
scanf("%f",&r);

if(r > 10) np = 6;
else {np = 8;}


init_environment();
printf("Enter 1 for Value Iteration, 2 for Policy Iteration, 3 to Exit: <1 or 2 or 3>: ");
scanf("%d",&decision);


	for (int i = 0; i <= 8 ;i++)
	{
		policy_it[i] = 'u';
	}

if(decision == 1) valueiteration();
else if(decision == 2) policyiteration();
else if(decision == 3) return 1;


	return 0;
}