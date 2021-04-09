#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define AVAILABLE 0
#define OCUPIED 1

#define IDLE 2
#define THINKING 3
#define EATING 4

typedef struct {
    sem_t semaphore;
    int status;
} Fork;

typedef struct {
    Fork **forks;
    int n_forks;
} DiningTable;

typedef struct {
    int id;
    char *name;
    int status;
    int thinking_time;
    int eating_time;
    DiningTable * table;
} Philosopher;




int to_eat(Philosopher *philosoper, int time);
int to_think(Philosopher *philosoper, int time);
void * philosopher_behavior(void * arg);
DiningTable* create_table(int n_forks);
Philosopher* create_philosopher(int id, char *name, DiningTable *table, int thinking_time, int eating_time);
Philosopher* philosopher_creator(int id, DiningTable *table, int thinking_time, int eating_time);
Philosopher** create_philosophers(int number_of_philosophers, DiningTable *table, int thinking_time, int eating_time);