#include<stdio.h>
#include<pthread.h>
#define MAX_PORTS 5
pthread_mutex_t mutex;
pthread_cond_t port_available;
int ports_in_use=0;
void*client_thread(void*arg)
{
int client_id=*(int*)arg;
while(1)
{
pthread_mutex_lock(&mutex);
if(ports_in_use<MAX_PORTS)
{
printf("Client %d is using a port.\n",client_id);
ports_in_use++;
pthread_mutex_unlock(&mutex);
}
else
{
printf("Client %d is waiting for an available port.\n",client_id);
pthread_cond_wait(&port_available,&mutex);
}
}
return NULL;
}
int main()
{
pthread_t clients[MAX_PORTS];
int client_ids[MAX_PORTS];
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&port_available,NULL);
for(int i=0;i<MAX_PORTS;i++)
{
client_ids[i]=i+1;
pthread_create(&clients[i],NULL,client_thread,&client_ids[i]);
}
for(int i=0;i<MAX_PORTS;i++)
{
pthread_join(clients[i],NULL);
}
pthread_mutex_destroy(&mutex);
pthread_cond_destroy(&port_available);
return 0;
}
