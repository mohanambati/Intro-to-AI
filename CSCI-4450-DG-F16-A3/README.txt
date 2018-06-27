CSCI-4450 Assignment-3:

Folder contains
(Solution 2.3) prog.c

Please follow below steps to compile and execute all the Assignment-3 programs in "loki.ist.unomaha.edu" .

step 1:
go to path where program is present.

step 2: compile the program by using the command below.
	gcc -std=c99 prog.c
Eg: mambati@loki:~$ gcc -std=c99 prog.c

step 3:
After successfull compilation without any errors (** or only with warnings**) you should be able to see "a.out" file in the same path.

step 4: Run "a.out" file using below command.
	./a.out 

	There are 2 options you can execute,
	Option1: ./a.out (Program promts for input query.)

	Eg: mambati@loki:~$ ./a.out 

	Option2: ./a.out help (prorgam displays the notation of random variables and promts for input query.)

	Eg: mambati@loki:~$ ./a.out help

step 5: Enter the query

         ---- Notation of Random Variables in Program ----------
         Education is high = 'e'   	Education is low = '~e'
         Teaching is high = 't'    	Teaching is low = '~t'
         Research is high = 'r'    	Research is low = '~r'
         Service is high = 's'     	Service is low = '~s'
         Performance is high = 'p'    Performance is low = '~p'
         AND = ','
         -------------------------------------------------------

Please enter the query as follows:  

p(<query variable sepertaed by ','>|<evidence varibales seperated by ','>)

(**Note: Dont give space in between the charecters.**)


Eg:-
---------------------------------------------------------------------------------------------------------------
Normal query                                                  					    |	Program Input query
===============================================================================================================
p(performance = high | education = high) 									    	|	p(p|e)
---------------------------------------------------------------------------------------------------------------
p(service=high | teaching = low AND performance = high)		                     	|	p(s|~t,p)
---------------------------------------------------------------------------------------------------------------
p(education = low | teaching = high AND performance = low)	                    	|	p(~e|t,~p)
---------------------------------------------------------------------------------------------------------------
p(education = low AND teaching = high AND Research = High AND performance = low)	|	p(~e,t,r,~p)
---------------------------------------------------------------------------------------------------------------



(**Note: Run the program again to enter a new query.(Re-start from step-4)**)
