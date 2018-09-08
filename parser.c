#include "parser.h"

void parse_file(FILE *in, int *mem, int *reg, char *filename) {

    char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *symbols = " 0123456789#,-";
    //number of line we're at
    int number = 0;

    //read file while it's not over
    while (!feof(in)) {

        //buf for read symbols
        char *buf = calloc(32, sizeof(char));
        if (buf == NULL){
            printf("Error: can't get memory\n");
            exit(1);
        }
        //int to get any symbol from input
        int read_symb = 0;
        unsigned int counter = 0;

        do {
            //get one symbol from file
            read_symb = fgetc(in);
            char* abc = strchr(alphabet, (char) read_symb);
            char* num = strchr(symbols, (char)read_symb);
            //error if it's not a latin symbol, number or comma or any sign
            if (read_symb == 10 || read_symb == EOF) //10 == '\n' >122 - символы другого алфавита
                break;
            else if ((abc == NULL && num == NULL) || read_symb > 122) {
                printf("Error 102: unknown symbol at line %d\n", number);
                printf("%c", read_symb);
                exit(102);
            }

            if (counter > sizeof(buf)) {
                buf = (char *) realloc(buf, sizeof(buf) + sizeof(char) * 32);
                if (buf == NULL){
                    printf("Error: can't get memory\n");
                    exit(1);
                }

            } else if (counter >= 100) { //слишком длинная строка
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
}