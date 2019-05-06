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
    int *Array;
	key = 2211;
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	if((Array = shmat(shmid, NULL, 0)) == (int*) -1)
		die("shmat");
	for(int i=0;i<MAXSIZE;i++)
	{
	  
	  	*(Array+i)=rand()%10;
	}
	while(*shm != '*')
		sleep(5);

	exit(0);
}

