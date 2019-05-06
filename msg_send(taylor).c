#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
//message send
struct Taylor
{
	long mtype;
	long double num;
};

int main(void)
 {
	struct Taylor x;
	int msgid;
	key_t key;
	
   	printf("Enter the value of x to compute exp(x) using taylor series: ");
   	scanf("%Lf",&x.num);

	if((key = ftok("msg_send(taylor).c",'b')) == -1 )
	{
		perror("key");
		exit(1);
	}
	if((msgid=msgget(key,0644|IPC_CREAT)) == -1 )
	{
		perror("key");
		exit(1);
	}

	x.mtype=1;

	if(msgsnd(msgid,&x,sizeof(x),0) == -1) 
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
