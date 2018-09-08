#include "main.h"

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int reg[8] = {0};
    int mem[1024] = {0};

    //if we have a wrong ammount of arguments - put an error on screen
    if (argc < 3 || argc > 4) {
        printf("error 300: you should write at least 2 arguments\nfor example:\nrisc.exe in.txt out.txt [debug]\n");
        printf("Example of input file:\n");
        printf("ADDI R1,R2,60\nADDI R2,R1,100\nADD R1,R2,R0\nNOP\n");
        exit(300);
    }
    in = fopen(argv[1], "r");

    if (in == NULL) {
        printf("error 200: file %s not found\n", argv[1]);
        exit(200);
    }

    //read input file and process it immediately
    //and close it afterwards
    //if no debug keyword
    if (argc == 3) {
        parse_file(in, mem, reg, argv[1]);
    } else
        //if there is a debug keyword
    if (argv[3] != NULL && strcmp(argv[3], "debug") == 0) {
        printf("starting debug mode\n");
        debug_file(in, mem, reg, argv[1]);
    } else {
        //if not debug
        printf("unknown command. \nPlease use [debug] for debugging or leave a blank space \n");
        exit(102);
    }

    //close input file
    fclose(in);

    //create an output file
    out = fopen(argv[2], "w");

    //print the registers content in it
    print_result(out, reg);
    fclose(out);

}