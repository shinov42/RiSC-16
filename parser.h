#ifndef C_PARSER_H
#define C_PARSER_H
#include <stdio.h>
#include "print.h"
#include "debug.h"
#include "simulation.h"
#include <stdlib.h>

void parse_file(FILE *in, int mem[], int reg[], char *filename);

#endif //C_PARSER_H