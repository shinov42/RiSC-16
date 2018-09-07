#include "debug.h"

void debug_file(FILE *in, int *mem, int *reg, char *filename) {
    //number of line we're at
    int number = 0;
    //whole alphabet to check if symbols are correct
    char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *symbols = " 0123456789#,-";
    //get a symbol from console
    char code = '\0';
    restart:
    printf("for next step of debugging press d\n");
    printf("if you want to exit debugging press e\n");
    if (!feof(in)) {
        start:
        scanf("%c", &code);
        //while file's not over
        if (code == 'd') {
            if (!feof(in)) {

                //buf for read symbols
                char *buf = calloc(32, sizeof(char));
                //int to get any symbol from input
                int read_symb = 0;

//number of symbol we read
                unsigned int counter = 0;

                do {
                    //get one symbol from file
                    read_symb = fgetc(in);
                    char *abc = strchr(alphabet, (char) read_symb);
                    char *num = strchr(symbols, (char) read_symb);
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
                if (buf[0] == '#');
                    //if not NULL or comment
                else
                    //need to process the string
                    string_procession(buf, in, mem, reg, number, filename);

                free(buf);
            }
            print_reg_debug(reg);
        } else if (code == 'e') {
            while (!feof(in)) {

                //buf for read symbols
                char *buf = calloc(32, sizeof(char));
                //int to get any symbol from input
                int read_symb = 0;
                //number of symbol we read
                unsigned int counter = 0;

                do {
                    //get one symbol from file
                    read_symb = fgetc(in);
                    char *abc = strchr(alphabet, (char) read_symb);
                    char *num = strchr(symbols, (char) read_symb);
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
        } else if (code != '\n') {
            printf("unknown command\n");
            goto restart;
        }
        if (!feof(in))
            goto start;

    }
}