/********************************************************************************************************************************************************/
// Title: CSCI 8456 Assignment-3                                            
// Written By: Mohan Sai Ambati.
// Program Name: prog.c
// 
// Description:
//	
//  This program prompts the user to enter a probability query for baysiean network in question 2 and this program will answer the queries using liklihood weighted sampling. 
//  
//
/********************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***********************************************************************************************************************************************************/
//     Definitions.
/***********************************************************************************************************************************************************/
#define N 10000
/***********************************************************************************************************************************************************/
//     Data Structures.
/***********************************************************************************************************************************************************/
struct Sample  {
	float weight;
	int data[5];
};

struct Node  {
	int value;
	float probability;
	char name;
	struct Node* parent[2];
	struct Node* child[2];
};

struct Node* education;
struct Node* teaching;
struct Node* research;
struct Node* service ;
struct Node* performance;

char query[128];
char query_variables[10];
char evidence_variables[10];
int result[5] = {2,2,2,2,2};
float totalweight = 0.0f;
/***********************************************************************************************************************************************************/
//    Create Bayseian Network.
/***********************************************************************************************************************************************************/
void create_BayseianNetwork(void)
{
education = (struct Node*) malloc(sizeof(struct Node));
teaching = (struct Node*) malloc(sizeof(struct Node));
research = (struct Node*) malloc(sizeof(struct Node));
service = (struct Node*) malloc(sizeof(struct Node));
performance = (struct Node*) malloc(sizeof(struct Node));

education->name = 'e';
education->parent[0]=NULL;
education->parent[1]=NULL;
education->parent[2]=NULL;
education->value= 2;

education->child[0]=teaching;
education->child[1]=research;


teaching->name = 't';
teaching->parent[0]=education;
teaching->parent[1]=NULL;
teaching->parent[2]=NULL;
teaching->value= 2;

teaching->child[0]=performance;
teaching->child[1]=NULL;


research->name = 'r';
research->parent[0]=education;
research->parent[1]=NULL;
research->parent[2]=NULL;
research->value= 2;

research->child[0]=performance;
research->child[1]=NULL;


service->name = 's';
service->parent[0]=NULL;
service->parent[1]=NULL;
service->parent[2]=NULL;
service->value= 2;

service->child[0]=performance;
service->child[1]=NULL;


performance->name = 'p';
performance->parent[0]=teaching;
performance->parent[1]=research;
performance->parent[2]=service;
performance->value= 2;

performance->child[0]=NULL;
performance->child[1]=NULL;

}

/***********************************************************************************************************************************************************/
//    This function generates a random number between 0 to 1.
/***********************************************************************************************************************************************************/
double genrandom()
{
    return (double)rand() / (double)RAND_MAX ;
}

/***********************************************************************************************************************************************************/
//    This function parses the user entered query.
/***********************************************************************************************************************************************************/

int parse_query()
{
	int len = 0, countQ = 0, countE = 0;
	int query_evidence_switch = 0; //if 0 query variable , if 1 evidence variable.
	len = strlen(query);

	for(int i = 0; i < len; i++)
	{
		if(query[i] == 'p' || query[i] == '(' || query[i] == 'e' || query[i] == '~' || query[i] == ',' || query[i] == 't' || query[i] == 'r' || query[i] == 's' ||query[i] == ')'|query[i] == '|' ){}
		else{printf("Please enter random variables in the list. [e,t,r,s,p] \n");
			return 0;}
	}

	if(query[0]!='p' || query[1] != '(' || query[len-1] != ')'|| query[2] == '|')
	{
		printf("Please enter the input as < p(query variables | evidence variables) > .\n");
		return 0;
	}

	for(int i = 2 ; i < len; i ++)
	{
		if(query[i] == '|' || query[i] == ')') {query_evidence_switch = 1; i++;}
	
		if(!query_evidence_switch && query[i] != ',')
		{
			query_variables[countQ] = query[i];
			countQ++;
		}
		else if(query[i] != ',')
		{
			evidence_variables[countE] = query[i];
			countE++;
		}

	}

	return 1;

}

/***********************************************************************************************************************************************************/
//    This function fixes the evidence variables.
/***********************************************************************************************************************************************************/

void fix_evidence()
{

	//read evidence varibales 
	int len = 0;
	len = strlen(evidence_variables);

	for(int i= 0 ; i < len ; i++)
	{
		if(evidence_variables[i] == 'e') education->value = 1;
		else if(evidence_variables[i] == 't') teaching->value = 1;
		else if(evidence_variables[i] == 's') service->value = 1;
		else if(evidence_variables[i] == 'p')	performance->value = 1;
		else if(evidence_variables[i] == 'r')	research->value = 1;

		else if(evidence_variables[i] == '~')
		{
			i++;
		if(evidence_variables[i] == 'e') education->value = 0;
		else if(evidence_variables[i] == 't') teaching->value = 0;
		else if(evidence_variables[i] == 's') service->value = 0;
		else if(evidence_variables[i] == 'p')	performance->value = 0;
		else if(evidence_variables[i] == 'r')	research->value = 0;


		}

	}
}

/***********************************************************************************************************************************************************/
//    This function checks if a variable is evidence or not.
/***********************************************************************************************************************************************************/

int is_evidence(char elem)
{
	int len = strlen(evidence_variables);
	for(int i =0; i<len ; i++)
	{
		if(evidence_variables[i] == elem) return 1; 
	}

	return 0;
}

/***********************************************************************************************************************************************************/
//    This function creates a sample depending upon CPT's.
/***********************************************************************************************************************************************************/


void create_sample(struct Sample* sample)
{
	float weight = 1.0f, random;
	float probability = 0.0f;
//******************Generate the education node in sample ***********************************************************************
	if(is_evidence('e')){
		if(education->value == 0) {probability = 0.3; sample->data[0] = 0;}
		else if(education->value == 1){ probability = 0.7; sample->data[0] = 1;}
		weight = weight * probability;
	}
	else
	{
		random = genrandom();
		if(random <= 0.7){education->value = 1; sample->data[0] = 1;}
		else if(random > 0.7){education->value = 0; sample->data[0] = 0;}

	}
//******************Generate the teaching node in sample ***********************************************************************
	if(is_evidence('t')){
	if(education->value == 1)
		if(teaching->value == 0) {probability = 0.55; sample->data[1] = 0;}
		else if(teaching->value == 1){ probability = 0.45; sample->data[1] = 1;}
		

	if(education->value == 0)
		if(teaching->value == 0) {probability = 0.85; sample->data[1] = 0;}
		else if(teaching->value == 1){ probability = 0.15; sample->data[1] = 1;}

		weight = weight * probability;
	}

	else
	{
		random = genrandom();

		if(education->value == 1)
		if(random <= 0.45){teaching->value = 1; sample->data[1] = 1;}
		else if(random > 0.45){teaching->value = 0; sample->data[1] = 0;}

		if(education->value == 0)
		if(random <= 0.15){teaching->value = 1; sample->data[1] = 1;}
		else if(random > 0.15){teaching->value = 0; sample->data[1] = 0;}

	}
//******************Generate the research node in sample ***********************************************************************
	if(is_evidence('r')){
	if(education->value == 1)
		if(research->value == 0) {probability = 0.15; sample->data[2] = 0;}
		else if(research->value == 1){ probability = 0.85; sample->data[2] = 1;}
		

	if(education->value == 0)
		if(research->value == 0) {probability = 0.65; sample->data[2] = 0;}
		else if(research->value == 1){ probability = 0.35; sample->data[2] = 1;}

		weight = weight * probability;
	}
	else
	{
		random = genrandom();

		if(education->value == 1)
		if(random <= 0.85){research->value = 1; sample->data[2] = 1;}
		else if(random > 0.85){research->value = 0; sample->data[2] = 0;}

		if(education->value == 0)
		if(random <= 0.35){research->value = 1; sample->data[2] = 1;}
		else if(random > 0.35){research->value = 0; sample->data[2] = 0;}

	}
//******************Generate the service node in sample ***********************************************************************
	if(is_evidence('s')){
		if(service->value == 0) {probability = 0.60; sample->data[3] = 0;}
		else if(service->value == 1){ probability = 0.40; sample->data[3] = 1;}

		weight = weight * probability;

	}
	
	else
	{
		random = genrandom();

		if(random <= 0.40){service->value = 1; sample->data[3] = 1;}
		else if(random > 0.40){service->value = 0; sample->data[3] = 0;}

	}
//******************Generate the Performance node in sample ***********************************************************************
	if(is_evidence('p')){
		if(teaching->value == 0){
			if(research->value == 0){
				if(service->value == 0){
					if(performance->value == 0){probability = 0.95; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.05; sample->data[4] = 1;}
				}
				else if(service->value == 1){
					if(performance->value == 0){probability = 0.95; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.05; sample->data[4] = 1;}
				}}
			else if(research->value == 1){
				if(service->value == 0){
					if(performance->value == 0){probability = 0.5; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.5; sample->data[4] = 1;}
				}
				else if(service->value == 1){
					if(performance->value == 0){probability = 0.5; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.5; sample->data[4] = 1;}
				}}}
		else if(teaching->value == 1){
			if(research->value == 0){
				if(service->value == 0){
					if(performance->value == 0){probability = 0.7; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.3; sample->data[4] = 1;}
				}
				else if(service->value == 1){
					if(performance->value == 0){probability = 0.7; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.3; sample->data[4] = 1;}
				}}
			else if(research->value == 1){
				if(service->value == 0){
					if(performance->value == 0){probability = 0.2; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.8; sample->data[4] = 1;}
				}
				else if(service->value == 1){
					if(performance->value == 0){probability = 0.05; sample->data[4] = 0;}
					else if(performance->value == 1){probability = 0.95; sample->data[4] = 1;}
				}}}

				weight = weight * probability;
	}
	else
	{
		random = genrandom();

		if(service->value == 0 && research->value == 0 && teaching->value == 0  ){
		if(random <= 0.05){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.05){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 0 && research->value == 0 && service->value == 1  ){
		if(random <= 0.05){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.05){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 0 && research->value == 1 && service->value == 0  ){
		if(random <= 0.5){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.5){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 0 && research->value == 1 && service->value == 1  ){
		if(random <= 0.5){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.5){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 1 && research->value == 0 && service->value == 0  ){
		if(random <= 0.3){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.3){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 1 && research->value == 0 && service->value == 1 ){
		if(random <= 0.3){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.3){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 1 && research->value == 1 && service->value == 0  ){
		if(random <= 0.8){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.8){performance->value = 0; sample->data[4] = 0;}}

		else if(teaching->value == 1 && research->value == 1 && service->value == 1  ){
		if(random <= 0.95){performance->value = 1; sample->data[4] = 1;}
		else if(random > 0.95){performance->value = 0; sample->data[4] = 0;}}
		

	}

 totalweight = totalweight + weight;
	sample->weight = weight;

}

/***********************************************************************************************************************************************************/
//    This function fixes the evidence variables.
/***********************************************************************************************************************************************************/

void formresult()
{
 
	int len = 0;
	len = strlen(query_variables);

	for(int i= 0 ; i < len ; i++)
	{
		

		if(query_variables[i] == 'e') result[0] = 1;
		else if(query_variables[i] == 't') result[1] = 1;
		else if(query_variables[i] == 's') result[3] = 1;
		else if(query_variables[i] == 'p')	result[4] = 1;
		else if(query_variables[i] == 'r')	result[2] = 1;

		else if(query_variables[i] == '~')
		{
			i++;
		if(query_variables[i] == 'e') result[0] = 0;
		else if(query_variables[i] == 't') result[1]= 0;
		else if(query_variables[i] == 's') result[3] = 0;
		else if(query_variables[i] == 'p')	result[4] = 0;
		else if(query_variables[i] == 'r')	result[2] = 0;


		}



	}
}

/***********************************************************************************************************************************************************/
//   This function checks the sample if it is equal to given query or not.
/***********************************************************************************************************************************************************/
int checksample(struct Sample* sample, int mat[4])
{
		if(mat[0] != 2)
		 {if(mat[0] != sample->data[0]) return 0;}

		if(mat[1] != 2)
		 {if(mat[1] != sample->data[1]) return 0;}

		if(mat[2] != 2)
		 {if(mat[2] != sample->data[2]) return 0;}

		if(mat[3] != 2)
		 {if(mat[3] != sample->data[3]) return 0;}

		if(mat[4] != 2)
		 {if(mat[4] != sample->data[4]) return 0;}

		return 1;
						
}
/***********************************************************************************************************************************************************/
//   This function prints the notation of variables used in the program.
/***********************************************************************************************************************************************************/

void init(void)
{
	printf("\t ---- Notation of input --------\n");
	printf("\t Education is high = 'e' \t Education is low = '~e' \n");
		printf("\t Teaching is high = 't' \t Teaching is low = '~t' \n");
			printf("\t Research is high = 'r' \t Research is low = '~r' \n");
				printf("\t Service is high = 's' \t Service is low = '~s' \n");
					printf("\t Performance is high = 'p' \t Performance is low = '~p' \n");
						printf("\t AND = ','\n");
	printf("\t -----------------------------------\n");

	printf("Please enter the query as follows:  p(<query variable sepertaed by ',''>|<evidence varibales seperated by ','>)\n");
}
/***********************************************************************************************************************************************************/
//    Main function controles the flow of the program.
/***********************************************************************************************************************************************************/
int main(int argc, char *argv[])
{
if(argc == 2)
{
	printf("%s\n",argv[1] );
	init();
}

	float prob,prob2;
	float w = 0.0f, w2 = 0.0f;


struct Sample* sample[N];

		create_BayseianNetwork();
			totalweight = 0.0f;
			w = 0.0f;
	
	printf("Enter the query:  ");
	scanf("%s",&query);

	if(!strcmp(query,"exit")) exit(-1);

	if(parse_query())
	{
		fix_evidence();

		for(int i =0 ; i <= N; i++)
		{
			sample[i] = (struct Sample*) malloc(sizeof(struct Sample));
			create_sample(sample[i]);
		}

		formresult();

		for (int i = 0; i < N; i++)
		{
			if(checksample(sample[i], result)){  w = w + sample[i]->weight;}
		}

		prob = w/totalweight;

		printf("%s: %f\n",query, prob);

	}

	return 0;
}
//----------------------------------------------------------End of Program ---------------------------------------------------------------------