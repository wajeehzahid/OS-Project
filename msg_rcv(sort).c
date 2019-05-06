#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#define SIZE 10
//message recieve
struct Sort
{
	long mtype;
	int num[SIZE];
};

int main(void) {
  	struct	Sort Array;
	int msgid;
	key_t key;

	if((key = ftok("msg_send(sort).c",'b')) == -1)
	{
		perror("key");
		exit(1);
	}

	if((msgid=msgget(key,0644)) == -1)
	{
		perror("msgid");
		exit(1);
	}

	if(msgrcv(msgid,&Array,sizeof(Array),1,0) == -1) 
	{
		perror("msgrcv");
		exit(1);
	}

	printf("Elements to Sort:\n");
	for(int i=0;i<SIZE;i++)
	{
		printf("%d,",Array.num[i]);
	}
	int swapped=0;

	for(int i=0;i<SIZE/2-1;i++)
	{
		for(int j=i;j<SIZE-i-1;j++)
		{
			if(Array.num[j]>Array.num[j+1])
			{
				int temp=Array.num[j];
				Array.num[j]=Array.num[j+1];
				Array.num[j+1]=temp;
				swapped=1;
			}
		}
		for(int j=SIZE-i-2;j>i;j--)
		{
			if(Array.num[j]<Array.num[j-1])
			{
				int temp=Array.num[j];
				Array.num[j]=Array.num[j-1];
				Array.num[j-1]=temp;
				swapped=1;
			}
		}
		if(swapped==0)
		break;
	}
	printf("\nSorted Array:\n");
	for(int i=0;i<SIZE;i++)
	{
		printf("%d,",Array.num[i]);
	}

    printf("\n");
	return 0;
}
