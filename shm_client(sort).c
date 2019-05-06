#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
void die(char *str) 
{
	perror(str);
	exit(1);
}

int main(void) {
	int shmid;
	key_t key1;
	int *Array;
	char *shm;
    
	key1=2211;

	fflush(stdin);
	if((shmid = shmget(key1, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((Array = shmat(shmid, NULL, 0)) == (int*) -1)
		die("shmat");
	if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");

	printf("Elements to Sort: \n");
	for(int i=0;i<MAXSIZE;i++)
	{
	  	printf("%d,",*(Array+i));
	}

    int swapped=0;
	for(int i=0;i<MAXSIZE/2-1;i++)
	{
		for(int j=i;j<MAXSIZE-i-1;j++)
		{
			if(Array[j]>Array[j+1])
			{
				int temp=Array[j];
				Array[j]=Array[j+1];
				Array[j+1]=temp;
				swapped=1;
			}
		}
		for(int j=MAXSIZE-i-2;j>i;j--)
		{
			if(Array[j]<Array[j-1])
			{
				int temp=Array[j];
				Array[j]=Array[j-1];
				Array[j-1]=temp;
				swapped=1;
			}
		}
		if(swapped==0)
		break;
	}
	printf("\nSorted Array:\n");
	for(int i=0;i<MAXSIZE;i++)
	{
		printf("%d,",Array[i]);
	}
     
	*shm = '*';
	
	printf("\n");
	exit(0);
}