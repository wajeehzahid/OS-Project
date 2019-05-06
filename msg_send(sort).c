#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define SIZE 10
//message send
struct Sort
{
	long mtype;
	int num[SIZE];
};

int main(void)
 {
	struct Sort Array;
	int msgid;
	key_t key;
    srand(time(NULL));
   	for (int i = 0; i < SIZE; ++i)
   	{
   		Array.num[i]=rand()%10;
   	}

	if((key = ftok("msg_send(sort).c",'b')) == -1 )
	{
		perror("key");
		exit(1);
	}
	if((msgid=msgget(key,0644|IPC_CREAT)) == -1 )
	{
		perror("key");
		exit(1);
	}

	Array.mtype=1;
	
	if(msgsnd(msgid,&Array,sizeof(Array),0) == -1) 
	{
		perror("msgsnd");
		exit(1);
	}
	sleep(10);
	if(msgctl(msgid,IPC_RMID,NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	return 0;
}
