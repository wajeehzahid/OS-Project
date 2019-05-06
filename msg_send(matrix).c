#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAXSIZE 10
//message send
struct Matrix
{
	long mtype;
	int Mat[MAXSIZE][MAXSIZE];

};

int main(void)
 {
	struct Matrix Matrix1,Matrix2;
	int msgid;
	key_t key;
    srand(time(NULL));
    for (int i = 0; i < MAXSIZE; i++)
    {
	    for (int j = 0; j < MAXSIZE; j++)
	    {
		    Matrix1.Mat[i][j] = rand()%10;
		    Matrix2.Mat[i][j] = rand()%10;
	    }
    }

	if((key = ftok("msg_send(matrix).c",'b')) == -1 )
	{
		perror("key");
		exit(1);
	}
	if((msgid=msgget(key,0644|IPC_CREAT)) == -1 )
	{
		perror("key");
		exit(1);
	}
	
	Matrix1.mtype=1;
	Matrix2.mtype=2; 
	if(msgsnd(msgid,&Matrix1,sizeof(Matrix1),0) == -1) 
	{
		perror("msgsnd");
		exit(1);
	}

	if(msgsnd(msgid,&Matrix2,sizeof(Matrix2),0) == -1) 
	{
		perror("msgsnd");
		exit(1);
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
	sleep(20);

	if(msgctl(msgid,IPC_RMID,NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	return 0;
}
