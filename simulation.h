#ifndef C_SIMULATION_H
#define C_SIMULATION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void string_procession(char *string, FILE *in, int *mem, int *reg, int number, char *filename);

void back_jump(int count, FILE *in, char *filename);

void skip_strings(int n, FILE *in);

#endif //C_SIMULATION_H