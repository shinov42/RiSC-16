#ifndef C_DEBUG_H
#define C_DEBUG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulation.h"
#include "print.h"

void debug_file(FILE *in, int *mem, int *reg, char *filename);

#endif //C_DEBUG_H