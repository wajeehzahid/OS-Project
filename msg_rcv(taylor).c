#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<math.h>
#include<pthread.h>
//message recieve
struct Taylor
{
	long mtype;
	long double num;
};

long double fact[150], pwr[150],s[1]; 
int i,term; 
struct Taylor x;

void *Power(void *temp) 
{     
	int k; 
	for(k=0;k<150;k++) 
	{  
		pwr[k] = pow(x.num,k); 
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
	s[0] = 0;    
	for(t=0;t<150;t++) 
		s[0] = s[0] +  (pwr[t] / fact[t]); 
	return s; 
}


int main(void) {
  	pthread_t thread1,thread2,thread3;   

	int msgid;
	key_t key;

	if((key = ftok("msg_send(taylor).c",'b')) == -1)
	{
		perror("key");
		exit(1);
	}

	if((msgid=msgget(key,0644)) == -1)
	{
		perror("msgid");
		exit(1);
	}

	if(msgrcv(msgid,&x,sizeof(x),1,0) == -1) 
	{
		perror("msgrcv");
		exit(1);
	}

	pthread_create(&thread1,NULL,Power,NULL); //calling power function  
	pthread_create(&thread2,NULL,Fact, NULL);  //calling factorial function  
	
	pthread_join(thread1,NULL);  
	pthread_join(thread2,NULL); 

	pthread_create(&thread3,NULL,Exp,NULL);  
	
	pthread_join(thread3,NULL); 

	printf("\nEXPONENTIAL Value of exp(%.2Lf) is : %Lf\n\n",x.num,s[0]);
	return 0;
}