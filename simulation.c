#include "simulation.h"

void string_procession(char *string, FILE *in, int mem[], int reg[], int number, char *filename) {
   //флаги чтобы понять что  аргумент - номер регистра
    int ra = 0, rb = 0, rc = 0;
    //служебная переменная
    int null_comp;
    //переменные для хранения чисел их аргументов
    int arg_one = 0, arg_two = 0, arg_three = 0;
    //массивы для проверки допустимых знаков
    char *numbers = {"01234567"};
    char *letterssymb = {"rR-"};
    //массив для хранения команды
    char comm[5] = {'\0'};
    //массив для хранения операндов
    char *operands;
    //получаем команду из строки
    //находим пробел
    char *temp1 = strchr(string, ' ');
    //ищем запятую (на будущее)
    char *commafind = strchr(string, ',');
    //находим количества символов до пробела
    size_t count = strchr(string, ' ') - string;
    //проверяем на отсутствие аргументов
    char* countnop = strchr(string, ' ');
    //если нет аргументов - переходим к обработке
    if (countnop == NULL){
        strcpy(comm, string);
        goto procession;
    }
    else
        //если не можем найти запятую
    if (count > sizeof(string))
        count = strchr(string, '\n') - string;
    //if command is too long - exit with code 100 - unknown command
    if (count > 5) {
        printf("Error 100: unknown command at line %d\n", number);
        exit(100);
    }

    //если есть аргументы вообще
    if (temp1 != NULL) {
        //put a command into 'comm'
        strncpy(comm, string, count);

        //put operands into 'operands'
        operands = string + count + 1;

        //нет ни одного операнда + нет запятой
//        if (operands != NULL && commafind == NULL) {
//            printf("Error 300: wrong argument at line %d", number);
//            exit(300);
//        }

        //operands: r1,r2,imm or r1,r2,r2 or r1,r2 or none
        //находим где запятая (по идее после первого аргумента)
        size_t comma = strchr(operands, ',') - operands;
        //массивы для операндов
        char string_operand_one[16] = {'\0'};
        char string_operand_two[16] = {'\0'};
        char string_operand_three[16] = {'\0'};
        //берём первый операнд (от начала до запятой)
        strncpy(string_operand_one, operands, comma);
        //проверка на то, нет ли там неразрешенных символов
        unsigned int k = 0;
        for (k = 0; k < sizeof(string_operand_one); k++) {
            char *checksymbols = strchr(letterssymb, string_operand_one[k]);
            char *checknumbers = strchr(numbers, string_operand_one[k]);
            if (checksymbols == NULL && checknumbers == NULL && string_operand_one[k] != '\0') {
                printf("Error 300: wrong argument at line %d", number);
                exit(300);
            }
        }

        //проверка на то что после R идёт номер регистра
        char *check_number = strchr(numbers, string_operand_one[1]);
        //ищем следующую запятую
        char *find_comma = strchr(string_operand_one, ',');
        //если не нашли - ошибка
        if (find_comma != NULL) {
            printf("Error 300: wrong argument at line %d", number);
            exit(300);
        }
        //
        if (/*temp1 == NULL &&*/ commafind == NULL)
            goto procession;
        //проверка что первая буква обозначает регистр (числа здесь быть не должно)
        else if ((string_operand_one[0] != 'R' && string_operand_one[0] != 'r') || check_number == NULL) {
            printf("Error 301: wrong argument at line %d", number);
            exit(301);
        } else {
            //идем брать второй операнд
            //get second operand string
            operands = operands + comma + sizeof(char);
            //сразу ищем и следующую
            char *temp = strchr(operands, ',');
            int check_comma = strcmp(operands, ",");
            if (check_comma == 0) {
                printf("Error 300: wrong ammount of arguments at line %d", number);
                exit(300);
            }
            //если есть второй и третий (по запятой определили)
            //берём отдельно второй аргумент и проверяем на соответствие списку разрешённых символов
            if (temp != NULL && operands != NULL) {
                comma = strchr(operands, ',') - operands;
                strncpy(string_operand_two, operands, comma);
                for (k = 0; k < sizeof(string_operand_two); k++) {
                    char *checksymbols = strchr(letterssymb, string_operand_two[k]);
                    char *checknumbers = strchr(numbers, string_operand_two[k]);
                    if (checksymbols == NULL && checknumbers == NULL && string_operand_two[k] != '\0') {
                        printf("Error 300: wrong argument at line %d", number);
                        exit(300);
                    }
                }
                //сравниваем, не пустая ли строка
                null_comp = strcmp(string_operand_two, "\0");
                if (null_comp == 0) {
                    printf("Error 300: wrong ammount of arguments at line %d", number);
                    exit(300);
                }

//                find_comma = strchr(string_operand_two, ',');
//                if (find_comma != NULL) {
//                    printf("Error 300: wrong ammount of arguments at line %d", number);
//                    exit(300);
//                }
                //проверка на то что после второго операнда лишь запятая
                char *temp_operands = operands + comma;
                check_comma = strcmp(temp_operands, ",");
                if (check_comma == 0) {
                    printf("Error 300: wrong ammount of arguments at line %d", number);
                    exit(300);
                }
                //проверяем строку и если всё нормально - передаём в третий аргумент
                operands = operands + comma + sizeof(char);
                check_comma = strcmp(operands, ",");
                if (check_comma == 0) {
                    printf("Error 300: wrong ammount of arguments at line %d", number);
                    exit(300);
                }
                strncpy(string_operand_three, operands, comma + 1);
                //проверяем третий аргумент на соответствие
                for (k = 0; k < sizeof(string_operand_three); k++) {
                    char *checksymbols = strchr(letterssymb, string_operand_three[k]);
                    char *checknumbers = strchr(numbers, string_operand_three[k]);
                    if (checksymbols == NULL && checknumbers == NULL && string_operand_three[k] != 0) {
                        printf("Error 300: wrong argument at line %d", number);
                        exit(300);
                    }
                }

//                find_comma = strchr(string_operand_three, ',');
//                if (find_comma != NULL) {
//                    printf("Error 300: wrong ammount of arguments at line %d", number);
//                    exit(300);
//                }
                //если осталось ещё что-то - ошибка
                operands = operands + sizeof(string_operand_three);
                if (operands[0] != '\0') {
                    printf("Error 300: wrong ammount of arguments at line %d", number);
                    exit(300);
                }

            }
            //выполняется если есть только второй аргумент (без третьего)
            else
            {
                strcpy(string_operand_two, operands);
                for (k = 0; k < sizeof(string_operand_two); k++) {
                    char *checksymbols = strchr(letterssymb, string_operand_two[k]);
                    char *checknumbers = strchr(numbers, string_operand_two[k]);
                    if (checksymbols == NULL && checknumbers == NULL && string_operand_two[k] != '\0') {
                        printf("Error 300: wrong argument at line %d", number);
                        exit(300);
                    }
                }
                null_comp = strcmp(string_operand_two, "\0");
                if (null_comp == 0) {
                    printf("Error 300: wrong ammount of arguments at line %d", number);
                    exit(300);
                }
            }
        }

        //переводим строки в числа и проверяем на номер если регистр
        arg_one = atoi(string_operand_one + sizeof(char));
        ra = 1;
        if (arg_one > 7 || arg_one < 0) {
            printf("error 105: can't reach specified register\n");
            exit(105);
        }
        check_number = strchr(numbers, string_operand_two[1]);
        if ((string_operand_two[0] == 'r' || string_operand_two[0] == 'R') && check_number != NULL) {
            rb = 1;
            arg_two = atoi(string_operand_two + sizeof(char));
            if (arg_two > 7 || arg_two < 0) {
                printf("error 105: can't reach specified register\n");
                exit(105);
            }
        } else
            arg_two = atoi(string_operand_two);

        check_number = strchr(numbers, string_operand_three[1]);
        if ((string_operand_three[0] == 'r' || string_operand_three[0] == 'R') && check_number != NULL) {
            rc = 1;
            arg_three = atoi(string_operand_three + sizeof(char));
            if (arg_three > 7 || arg_three < 0) {
                printf("error 105: can't reach specified register\n");
                exit(105);
            }
        } else
            arg_three = atoi(string_operand_three);
    } else strcpy(comm, string);

    //basic commands

    procession:
    //reg1 = reg2 + reg3
    if (strcmp(comm, "ADD") == 0) {
        //operands should contain r1,r2,r3
        if (ra == 1 && rb == 1 && rc == 1)
            reg[arg_one] = reg[arg_two] + reg[arg_three];
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //reg1 = reg2 + imm
    else if (strcmp(comm, "ADDI") == 0) {
        //operands should contain r1,r2,imm
        if (ra == 1 && rb == 1 && rc == 0)
            reg[arg_one] = reg[arg_two] + arg_three;
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //reg1 = nand(reg2, reg3)
    else if (strcmp(comm, "NAND") == 0) {
        //operands should contain r1,r2,r3
        if (ra == 1 && rb == 1 && rc == 1)
            reg[arg_one] = !(reg[arg_two] & reg[arg_three]);
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //top 10 bits of imm into 16-bit regA, rest are zeroes
    else if (strcmp(comm, "LUI") == 0) {
        //operands should contain r1,imm
        if (ra == 1 && rb == 0 && rc == 0)
            reg[arg_one] = (int) (arg_two & 01111111111000000);
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //store value from r1 to memory formed by imm+reg2
    else if (strcmp(comm, "SW") == 0) {
        //operands should contain r1,r2,imm
        //save reg into memory
        if (arg_three + reg[arg_two] > 1024) {
            printf("error 400: memory out of bounds\n");
            exit(400);
        }
        if (ra == 1 && rb == 1 && rc == 0)
            mem[reg[arg_two] + arg_three] = reg[arg_one];
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //load value from memory to reg1, mem is formed by imm+reg2
    else if (strcmp(comm, "LW") == 0) {
        //operands should contain r1,r2,imm
        if (arg_three + reg[arg_two] > 1024) {
            printf("error 400: memory out of bounds\n");
            exit(400);
        }
        if (ra == 1 && rb == 1 && rc == 0)
            reg[arg_one] = mem[reg[arg_two] + arg_three];
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //branch if equal => if r1==r2, branch to PC+1+imm, where PC is address of beq
    else if (strcmp(comm, "BEQ") == 0) {
        //operands should contain r1,r2,imm
        if (ra == 1 && rb == 1 && rc == 0 && reg[arg_one] == reg[arg_two])
           skip_strings(arg_three + 1, in);//skip imm+1 lines
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //jump and link to address from regB. Store PC+1 into regA
    else if (strcmp(comm, "JALR") == 0) {
        if (ra == 1 && rb == 1 && rc == 0) {
            if (reg[arg_two] > number)
                skip_strings(reg[arg_two] - number, in);//skip imm+1 lines
            else if (reg[arg_two] < number && reg[arg_two] > 0) {
                reg[arg_one] = number + 1;
               back_jump(reg[arg_two], in, filename);
            }
        } else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //additional commands
    else if (strcmp(comm, "NOP") == 0) {
        if (ra == 0 && rb == 0 && rc == 0)
            reg[0] = 0;
        else {
            printf("Error 301: wrong argument(s)\n");
            exit(301);
        }
    }

        //operands contain nothing
    else if (strcmp(comm, "MOVI") == 0) {
        //operands should contain r1,imm
        if (ra == 1 && rb == 0 && rc == 0)
            reg[arg_one] = arg_two;
        else {
            printf("error 300: wrong argument(s)\n");
            exit(300);
        }
    }

        //if we didn't recognise command
    else {
        printf("error 100: unknown command %s", comm);
        exit(100);
    }
}

void skip_strings(int n, FILE *in) {
    int count = n;

    //while file's not over
    while (!feof(in) && count != 0) {
        int buf = 1;
        while (buf != '\n')
            buf = fgetc(in);
        //counter minus one
        count--;
    }
}

void back_jump(int count, FILE *in, char *filename) {
    freopen(filename, "r", in);
    int buf = 1;

    //while file's not over
    while (!feof(in) && count != 0) {
        while (buf != '\n')
            buf = fgetc(in);
        //counter minus one
        count--;
    }
}