#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define n 5
sem_t room;
sem_t chopstick[n];
sem_t mutex;
void* philosopher(void* num){
int id=*(int*)num;
while(1){
printf("Philsopher %d is thinking\n",id);
sleep(1);
sem_wait(&room);
sem_wait(&chopstick[id]);
sem_wait(&chopstick[(id+1)%n]);
sem_wait(&mutex);
printf("Philsopher %d is eating\n",id);
sem_post(&mutex);
sleep(2);
sem_post(&chopstick[id]);
sem_post(&chopstick[(id+1)%n]);
sem_post(&room);
}}

int main(){
pthread_t tid[n];
int phil[n];
sem_init(&room,0,n-1);
sem_init(&mutex,0,1);
for(int i=0;i<n;i++){
sem_init(&chopstick[i],0,1);}
for(int i=0;i<n;i++){
phil[i]=i;
pthread_create(&tid[i],NULL,philosopher,&phil[i]);
}
for(int i=0;i<n;i++){
pthread_join(tid[i],NULL);}
return 0;
}