#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
//message recieve
#define MAXSIZE 10
struct Matrix
{
	long mtype;
	int Mat[MAXSIZE][MAXSIZE];
};

int main(void) {
  	struct	Matrix Matrix1,Matrix2,Result;
	int msgid;
	key_t key;

	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			Result.Mat[i][j]=0;
		}
	}
	if((key = ftok("msg_send(matrix).c",'b')) == -1)
	{
		perror("key");
		exit(1);
	}

	if((msgid=msgget(key,0644)) == -1)
	{
		perror("msgid");
		exit(1);
	}
	
	if(msgrcv(msgid,&Matrix1,sizeof(Matrix1),1,0) == -1) 
	{
		perror("msgrcv1");
		exit(1);
	}

	if(msgrcv(msgid,&Matrix2,sizeof(Matrix2),2,0) == -1) 
	{
		perror("msgrcv2");
		exit(1);
	}

	for(int i=0;i<MAXSIZE;i++)
    {
        for(int j=0;j<MAXSIZE;j++)
        {
            for(int k=0;k<MAXSIZE;k++)
            {
             	Result.Mat[i][j]+=Matrix1.Mat[i][k]*Matrix2.Mat[k][j];
            }
        }
    }
    printf("Matrix A:\n");
	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			printf("%d ",Matrix1.Mat[i][j]);
		}
		printf("\n");
	}
	printf("\n\nMatrix B:\n");
	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			printf("%d ",Matrix2.Mat[i][j]);
		}
		printf("\n");
	}
    printf("\n\nProduct of Matrix A and Matrix B: \n");
    for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			printf("%d ",Result.Mat[i][j]);
		}
		printf("\n");
	}
	return 0;
}
