#include "philosophers.h"

Fork* create_fork()
{
    Fork * new_fork = (Fork *) malloc(sizeof(Fork));
    new_fork->status = AVAILABLE;
    sem_init(&(new_fork->semaphore), 0, 1);
    return new_fork;   
}

Philosopher* create_philosopher(int id, char *name, DiningTable *table, int thinking_time, int eating_time)
{
    Philosopher * new_philosopher = (Philosopher *) malloc(sizeof(Philosopher));
    new_philosopher->id = id;
    new_philosopher->name = name;
    new_philosopher->status = 0;
    new_philosopher->table = table;
    new_philosopher->eating_time = eating_time;
    new_philosopher->thinking_time = thinking_time;
}

Philosopher* philosopher_creator(int id, DiningTable *table, int thinking_time, int eating_time)
{
    return create_philosopher(id, "", table, thinking_time, eating_time);
}

Philosopher** create_philosophers(int number_of_philosophers, DiningTable *table, int thinking_time, int eating_time)
{
    Philosopher ** new_philosophers = (Philosopher **) malloc(sizeof(Philosopher*) * number_of_philosophers);
    for(int i = 0; i < number_of_philosophers; i++)
    {
        new_philosophers[i] = philosopher_creator(i, table, thinking_time, eating_time);
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

void * philosopher_behavior(void * arg)
{
    Philosopher * my = (Philosopher *) arg;
    #ifdef DEBUG
        printf("|Log: Philosopher|%d| | Being started\n", my->id);
    #endif

    int successful_try = 0;
    while(successful_try == 0)
    {
        int right_fork = my->id;
        int left_fork = (my->id + 1) % my->table->n_forks;
        
        #ifdef DEBUG
            printf("|Log: Philosopher|%d| | Trying to get forks\n", my->id);
        #endif
        
        int right_fork_res = sem_trywait(&my->table->forks[right_fork]->semaphore);
        int left_fork_res = sem_trywait(&my->table->forks[left_fork]->semaphore);
        
        #ifdef DEBUG
            printf("|Log: Philosopher|%d| | Checking try\n", my->id);
        #endif
        
        if (right_fork_res == 0 && left_fork_res == 0)
        {   
            successful_try++;
            to_eat(my, 4);
            sem_post(&my->table->forks[right_fork]->semaphore);
            sem_post(&my->table->forks[left_fork]->semaphore);
        }else
        {
            if(right_fork_res == 0){
                sem_post(&my->table->forks[right_fork]->semaphore);
            }else if(left_fork_res == 0)
            {
                sem_post(&my->table->forks[left_fork]->semaphore);
            }

            #ifdef DEBUG
                printf("|Log: Philosopher|%d| | Going to think\n", my->id);
                printf("|Log: Philosopher|%d| | Starting to think\n", my->id);
            #endif
            to_think(my, 4);
            #ifdef DEBUG
                printf("|Log: Philosopher|%d| | Finish to think\n", my->id);
            #endif
        }
        
        
    }
    
    
}

int to_eat(Philosopher *philosoper, int time)
{
    printf("|Log: Philosopher|%d| Eating\n", philosoper->id);
    sleep(philosoper->eating_time);
    printf("|Log: Philosopher|%d| Finish\n", philosoper->id);

}


int to_think(Philosopher *philosoper, int time)
{
    printf("|Log: Philosopher|%d| Thinking\n", philosoper->id);
    sleep(philosoper->thinking_time);
    printf("|Log: Philosopher|%d| Finish\n", philosoper->id);

}