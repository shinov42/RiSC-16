#ifndef C_PARSER_H
#define C_PARSER_H
#include <stdio.h>
#include "print.h"
#include "debug.h"
#include "simulation.h"
#include <stdlib.h>

int parse_file(FILE *in, int mem[], int reg[], char *filename);

void get_argc(char** args, int argv);

#endif //C_PARSER_H