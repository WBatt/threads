#include "buffer.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <semaphore.h>
#include <unistd.h> //for sleep function


int sum; 
buffer *Buffer;
sem_t mutex;
sem_t full;
sem_t empty;
sem_t printing;

void *producer(void *param);
void *consumer(void *param);


//Parameter: how long the main thread sleeps before terminating (in seconds)
//Parameter: The number of producer threads
//Parameter: The number of consumer threads
int main(int argc, char *argv[])
    {
        srand (time(NULL));
        //1. Get command line arguments argv[1],argv[2],argv[3] 
        if (argc != 4)  //make sure you have 3 inputs
            {
                fprintf(stderr,"usage: a.out <integer value> <integer value> <integer value>\n");
                return -1;
            }
        if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0 || atoi(argv[3]) < 0) //make sure they are positive integers
            {
                fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
                return -1;
            }
            
        //2. Initialize buffer
        Buffer = new buffer;
        sem_init(&mutex, 0, 1);
        sem_init(&full, 0, 0);
        sem_init(&empty, 0, 5);
        sem_init(&printing, 0, 1);

        
        pthread_t tid;              //thread identifier
        pthread_attr_t attr;        //set of thread attributes    
        pthread_attr_init(&attr);   //get the default attributes
        
        //3. Create producer thread(s) 
        for(int i = 0; i < atoi(argv[2]); i++)
            {
                int *arg;
                arg = (int*)malloc(sizeof(int));
                *arg = i;
                pthread_create(&tid,&attr,producer, (void*) arg);
            }
        //4. Create consumer thread(s)
        for(int i = 0; i < atoi(argv[3]); i++)
            {
                int *arg;
                arg = (int*)malloc(sizeof(int));
                *arg = i;
                pthread_create(&tid,&attr,consumer, arg); 
            }
        //5. Sleep 
        usleep(atoi(argv[1]) * 1000000);
        
        pthread_join(tid,NULL);     //wait for the thread to exit
        printf("sum = %d\n",sum);
            
        //6. Exit 
        return -1;
    }
    
 
//need to sleep for random amounts of time
//upon wakening, insert a random number into the buffer
void *producer(void *param) 
    {
        printf("Creating producer thread.\n");
        buffer_item item;
        int done = 0;
        while (done < 5) 
            {
                usleep((rand() % 5 + 1) * 100000);
                
                item = rand() % 20 + 1;  // produce an item
                
                sem_wait(&empty);
                sem_wait(&mutex);
                
                
                // add the item to the buffer
                if(Buffer->insert_item(item))
                    {
                        printf("report error condition PRODUCER\n");
                    }
                else
                    {
                        printf("producer produced %d\n",item);
                    }
                

                sem_post(&mutex);
                sem_post(&full);
                
                sem_wait(&printing);
                Buffer->displayBuffer();
                sem_post(&printing);
                
                done++;
            }
            return NULL;
    }
    

//need to sleep for random amounts of time
//upon wakening, try to take something out of the buffer
void *consumer(void *param) 
    {
        printf("Creating consumer thread.\n");
        buffer_item item;
        int done = 0;
        while (done < 5) 
            {
                usleep((rand() % 5 + 1) * 100000);
                
                sem_wait(&full);
                sem_wait(&mutex);
                
                // consume the removed item
                if (Buffer->remove_item(&item))
                    {
                        printf("report error condition CONSUMER\n");
                    }
                else
                    {
                        printf("consumer consumed %d\n",item);
                    }

                sem_post(&mutex);
                sem_post(&empty);
                
                sem_wait(&printing);
                Buffer->displayBuffer();
                sem_post(&printing);
                
                done++;
   
            }
            return NULL;
    }
