#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void eat(int phil)
{
    printf("\n Philosopher %d is eating", phil);
}

void *philosopher(void *num)
{
    int phil = *(int *)num;
    sem_wait(&room);

    printf("\n Philosopher %d has entered room ", phil);
    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil + 1) % 5]);

    eat(phil);

    sleep(2);

    printf("\nPhilosopher %d has finished eating", phil);

    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    sem_post(&room);
}

int main()
{
    int i, a[5];
    pthread_t tid[5];
    sem_init(&room, 0, 4);

    for (int i = 0; i < 5; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (int i = 0; i < 5; i++)
    {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}