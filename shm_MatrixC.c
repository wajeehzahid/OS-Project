#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

#define SIZE 5
#define MAXSIZE 30
#define MAX_THREAD 4

int *MatrixA,*MatrixB;
int Product[SIZE][SIZE]={0};
int step_i = 0; 

void die(char *str) 
{
	perror(str);
	exit(1);
}
void* multi(void* arg) 
{ 
    int core = step_i++; 

    for (int i = core * SIZE / 4; i < (core + 1) * SIZE / 4; i++)  
        for (int j = 0; j < SIZE; j++)  
            for (int k = 0; k < SIZE; k++)  
                Product[i][j] += *(MatrixA+(i*SIZE+k)) * *(MatrixB+(k*SIZE+j)); 
} 

int main(void) {
	int shmid,shmid2;
	key_t key1,key2;
	char *shm1,*shm2;

	key1=2211;
    key2=2212;

	fflush(stdin);
	if((shmid = shmget(key1, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((MatrixA = shmat(shmid, NULL, 0)) == (int*) -1)
		die("shmat");
	if((shm1 = shmat(shmid, NULL, 0)) == (char*) -1)
		die("shmat");

    if((shmid2 = shmget(key2, MAXSIZE, IPC_CREAT | 0666)) < 0)
		die("shmget");
	if((MatrixB= shmat(shmid2, NULL, 0)) == (int*) -1)
		die("shmat");
	if((shm2 = shmat(shmid2, NULL, 0)) == (char*) -1)
		die("shmat");

	pthread_t threads[MAX_THREAD]; 
  
    for (int i = 0; i < MAX_THREAD; i++) { 
        pthread_create(&threads[i], NULL, multi,NULL); 
    } 
  
    for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);  
	printf("Product of Matrix A and Matrix B:\n");
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
			printf("%d ",Product[i][j]);
		printf("\n");
	}
	*shm1 = '*';
	*shm2 = '*';
	printf("\n");
	exit(0);
}

