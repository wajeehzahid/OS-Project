#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#define MAXSIZE 10 

void die(char *str) 
{
	perror(str);
	exit(1);
}

long double x,fact[150], pwr[150],sum; 
int i,term; 

void *Power(void *temp) 
{     
	int k; 
	for(k=0;k<150;k++) 
	{  
		pwr[k] = pow(x,k); 
	}  
	return pwr; 
} 

void *Fact(void *temp) 
{ 
	long double f;  
	int j; 
	fact[0] = 1.0; 
	for(term=1;term<150;term++) 
	{ 
		f = 1.0; 
		for(j=term;j>0;j--) 
			f = f * j; 
		fact[term] = f; 
	} 
	return fact; 
} 
void *Exp(void *temp) 
{ 
	int t; 
	sum = 0;    
	for(t=0;t<150;t++) 
		sum = sum +  (pwr[t] / fact[t]); 
	return NULL; 
}


int main(void) 
{
	pthread_t thread1,thread2,thread3;   
	int shmid;
	key_t key1;
	long double *shm1;
	char *shm2;
    
	key1=2211;
	fflush(stdin);
	if((shmid = shmget(key1, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm1 = shmat(shmid, NULL, 0)) == (long double*) -1)
		die("shmat");
	if((shm2 = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");

	x=*shm1;

	pthread_create(&thread1,NULL,Power,NULL); //calling power function  
	pthread_create(&thread2,NULL,Fact, NULL);  //calling factorial function  
	
	pthread_join(thread1,NULL);  
	pthread_join(thread2,NULL); 

	pthread_create(&thread3,NULL,Exp,NULL);  
	
	pthread_join(thread3,NULL); 

	printf("\nEXPONENTIAL Value of exp(%.2Lf) is : %Lf\n\n",x,sum);
     
	*shm2 = '*';
	
	printf("\n");
	exit(0);
}