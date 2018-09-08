#include "print.h"

void print_result(FILE *out, int* reg){
    fprintf(out, "registers: \n");
    for (int i = 0; i < 8; i++)
        fprintf(out, "reg[%d]: %d\n", i, reg[i]);
}