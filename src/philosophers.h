#include <stdio.h>
#include <stdlib.h>

#define AVAIABLE 0
#define OCUPIED 1

#define IDLE 2
#define THINKING 3
#define EATING 4

typedef struct {
    int id;
    char name[];
    int status;
} Philosopher;

typedef struct {
    int status;
} Spoon;

typedef struct {
    Philosopher philosophers[];
} Pensatorio;

typedef struct {
    Philosopher philosophers[];
    Spoon spoons[];
} MesaDeJantar;