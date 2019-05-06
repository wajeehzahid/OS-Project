#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
//A server
#define ROWSIZE 5
#define COLSIZE 5
#define MAXSIZE 30
void die(char *str) 
{
    printf("DIE");
	perror(str);
	exit(1);
}

int main(void) 
{
	srand(time(NULL));
	int shmid;
	key_t key;
	char *shm;
    int *MatrixA;
	key = 2211;
	if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");
	if((MatrixA = shmat(shmid, NULL, 0)) == (int*) -1)
		die("shmat");

	for(int i=0;i<ROWSIZE;i++)
	{
	  for(int j=0;j<COLSIZE;j++)
	  {
	  	*(MatrixA+(i*ROWSIZE+j))=rand()%10;
	  }
	}

	printf("Matrix A:\n");
	for(int i=0;i<ROWSIZE;i++)
	{
	  for(int j=0;j<COLSIZE;j++)
	  {
	  	printf("%d ",*(MatrixA+(i*ROWSIZE+j)));
	  }
	  printf("\n");
	}

	while(*shm != '*')
		sleep(2);

	exit(0);
}


