#include "philosophers.h"

Fork* create_fork()
{
    Fork * new_fork = (Fork *) malloc(sizeof(Fork));
    new_fork->status = AVAILABLE;
    sem_init(&(new_fork->semaphore), 0, 1);
    return new_fork;   
}

Philosopher* create_philosopher(int id, char *name, DiningTable *table)
{
    Philosopher * new_philosopher = (Philosopher *) malloc(sizeof(Philosopher));
    new_philosopher->id = id;
    new_philosopher->name = name;
    new_philosopher->status = 0;
    new_philosopher->table = table;
}

Philosopher* philosopher_creator(int id, DiningTable *table)
{
    Philosopher * new_philosopher = (Philosopher *) malloc(sizeof(Philosopher));
    new_philosopher->id = id;
    new_philosopher->name = "";
    new_philosopher->status = 0;
    new_philosopher->table = table;
}

Philosopher** create_philosophers(int number_of_philosophers, DiningTable *table)
{
    Philosopher ** new_philosophers = (Philosopher **) malloc(sizeof(Philosopher*) * number_of_philosophers);
    for(int i = 0; i < number_of_philosophers; i++)
    {
        new_philosophers[i] = philosopher_creator(i, table);
        #ifdef DEBUG
            printf("|Log: Philosopher|%d| Being created\n", new_philosophers[i]->id);
        #endif
    }
    return new_philosophers;
}

DiningTable* create_table(int n_forks)
{
    DiningTable * new_table = (DiningTable *) malloc(sizeof(DiningTable));
    new_table->forks = (Fork **) malloc(sizeof(DiningTable*) * n_forks);
    new_table->n_forks = n_forks;
    int i = 0;
    
    for(i; i < n_forks; i++)
    {
        new_table->forks[i] = create_fork();
    }

    return new_table;
}
