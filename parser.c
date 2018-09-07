#include "parser.h"

int parse_file(FILE *in, int *mem, int *reg, char *filename) {

    char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *symbols = " 0123456789#,-";
    //number of line we're at
    int number = 0;

    //read file while it's not over
    while (!feof(in)) {

        //buf for read symbols
        char *buf = calloc(32, sizeof(char));
        //int to get any symbol from input
        int read_symb = 0;
        unsigned int counter = 0;

        do {
            //get one symbol from file
            read_symb = fgetc(in);
            char* abc = strchr(alphabet, (char) read_symb);
            char* num = strchr(symbols, (char)read_symb);
            //error if it's not a latin symbol, number or comma or any sign
            if (read_symb == 10 || read_symb == EOF)
                break;
            else if ((abc == NULL && num == NULL) || read_symb > 122) {
                printf("Error 102: unknown symbol at line %d\n", number);
                printf("%c", read_symb);
                exit(102);
            }

            if (counter > sizeof(buf)) {
                buf = (char *) realloc(buf, sizeof(buf) + sizeof(char) * 32);
            } else if (counter >= 100) {
                printf("Error 103: command line %d is too long\n", number);
                exit(103);
            }

            buf[counter++] = (char) read_symb;
        } while (1);

        //number of string
        number++;

        //if comment
        if (buf[0] == '#')
            continue;
            //if not NULL or comment
        else
            //need to process the string
            string_procession(buf, in, mem, reg, number, filename);
        free(buf);
    }
    return 42;
}

void get_argc(char **argv, int argc) {
    FILE *in, *out;
    int reg[8] = {0};
    int mem[1024] = {0};

    //if we have a wrong ammount of arguments - put an error on screen
    if (argc < 3 || argc > 4) {
        printf("error 300: you should write at least 2 arguments\nfor example:\nin.txt out.txt [debug]\n");
        printf("Example of input file:\n");
        printf("ADDI R1,R2,60\nADDI R2,R1,100\nADD R1,R2,R0\nNOP\n");
        exit(300);
    }

    //open input file, process it and if there is a problem
    //put a warning on screen
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
    if (argv[3] != NULL) {

        if (strcmp(argv[3], "debug") == 0) {
            printf("starting debug mode\n");
            debug_file(in, mem, reg, argv[1]);
        }
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