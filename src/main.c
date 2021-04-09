#include "philosophers.h"

int main(int argc, char * args[]){
    if(argc != 4)
    {
        printf("ERROR: Number of arguments is wrong. \nYou need enter 3 arguments.\n|Number of filosophiers| Time to think| Time to Eat|\n");
        return 0;
    }else
    {
        int number_of_philosophers = atoi(args[1]);
        int time_to_think = atoi(args[2]);
        int time_to_eat = atoi(args[3]);

         #ifdef DEBUG
        printf("---------Features---------\n");
        printf("|Log: Number of philosophers = %d\n", number_of_philosophers);
        printf("|Log: Thinking time = %d\n", time_to_think);
        printf("|Log: Eating time = %d\n", time_to_eat);
        printf("--------------------------\n");
        #endif

        DiningTable * table;
        Philosopher **philosophers;
        table = create_table(number_of_philosophers);
        philosophers = create_philosophers(number_of_philosophers, table, time_to_think, time_to_eat);

        pthread_t threads[number_of_philosophers];

        
        philosopher_behavior(philosophers[0]);
        int ret, i;
        for (i = 0; i < number_of_philosophers; i++)
        {
            ret = pthread_create(&threads[i], NULL, &philosopher_behavior, philosophers[i]);
            if(ret != 0) {
                printf ("Create pthread error!\n");
                exit (1);
            }
        }
        
        for (i = 0; i < number_of_philosophers; i++) { 
            pthread_join(threads[i], NULL);
        }
    }    
}