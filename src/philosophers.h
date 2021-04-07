#include <stdio.h>
#include <stdlib.h>

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
    DiningTable * table;
} Philosopher;




int to_eat(Philosopher *philosoper, int time);
int to_think(Philosopher *philosoper, int time);
void * philosopher_behavior(void * arg);