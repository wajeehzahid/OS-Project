#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
//A server
#define MAXSIZE 10 
void die(char *str) 
{
    printf("DIE");
	perror(str);
	exit(1);
}

int main(void) 
{
	int shmid;
	key_t key;
	char *shm;
    long double x;
    long double* shm2;
	key = 2211;
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	if((shm2 = shmat(shmid, NULL, 0)) == (long double*) -1)
		die("shmat");

	
	printf("Enter the value of x to compute taylor series: ");
   	scanf("%Lf",&x);

   	*shm2=x;

	while(*shm != '*')
		sleep(1);

	exit(0);
}

