#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *f1;
FILE *f2;
char ch;
char code[100];

struct ArrayTable
{
    char name[10];
    char size[5];
    char type[10];
};
struct ArrayTable AT[20];

// Counter to keep our position in ArrayTable AT
int AT_counter = 0;

void getSizeFromAT(char *name, char *dest)
{
    // Find size of the given Array from ArrayTable AT
    int i;
    for (i = 0; i < 20; i++)
    {
        if (strcmp(AT[i].name, name) == 0)
        {
            strcpy(dest, AT[i].size);
            break;
        }
    }
}

void putIndent(int space, FILE *file)
{
    // Before for loops, we decided to put one line blank to make it more readable.
    // Put indent to the beginning of the code if source code has indents
    if (space != 0)
    {
        int i;
        for (i = 0; i < space; i++)
        {
            fputc(' ', file);
        }
    }
}

void clearString(char *array, int size)
{
    // Clear buffers (variables) every cycle of while
    int c;
    for (c = 0; c < size; c++)
    {
        array[c] = 0;
    }
}

void declare(char *name, char *size, char *type, int space)
{
    // Get variables and create a string suits to the definition
    char buffer[50];
    sprintf(buffer, "%s %s[%s];\n", type, name, size);

    // Send variables to the ArrayTable AT
    strcpy(AT[AT_counter].type, type);
    strcpy(AT[AT_counter].name, name);
    strcpy(AT[AT_counter].size, size);
    AT_counter++;

    // Put indent if requires
    putIndent(space, f2);

    // Send result to the file
    fputs(buffer, f2);
}

void read(char *file, char *name, int space)
{
    char buffer[200];
    char buffer1[200];
    char buffer2[200];
    int percent = 37; // ASCII code of percent (To print '%' in result)

    // Get size of the variable name which is given in the arguments
    char size[5];
    clearString(size, 5);
    getSizeFromAT(name, size);

    // Create a string suits to the definition
    sprintf(buffer, "FILE *ff=fopen(\"%s\",\"r\");\n", file);
    // printf("%s", buffer);

    // Put indent if requires
    putIndent(space, f2);

    // Send result to the file
    fputs(buffer, f2);

    sprintf(buffer1, "for (int i=0; i<%s; i++)\n", size);
    // printf("%s", buffer1);

    // To put indents to the next line, we should head to the next line first.
    fputs("\n", f2);

    putIndent(space, f2);
    fputs(buffer1, f2);

    sprintf(buffer2, "    fscanf(ff, \"%cd\" &%s[i]);\n", percent, name);
    // printf("%s", buffer2);
    putIndent(space, f2);
    fputs(buffer2, f2);

    putIndent(space, f2);
    fputs("close(ff);\n", f2);
}

void print(char *name, int space)
{
    char buffer[200];
    char buffer2[200];
    int percent = 37; // ASCII code of percent

    // Get size of the variable name which is given in the arguments
    char size[5];
    clearString(size, 5);
    getSizeFromAT(name, size);

    // For all lines:
    //    Create buffer string which suits to the definiton
    //    Put indent if requires (Before line of for loop, we should also put one line blank)
    //    Send result to the file
    sprintf(buffer, "for (int i=0; i<%s; i++)\n", size);
    // printf("%s", buffer);

    fputs("\n", f2); // Head to the next line before putting for loop
    putIndent(space, f2);
    fputs(buffer, f2);

    sprintf(buffer2, "    printf(\"%cd\", &%s[i]);\n", percent, name); // We should put additional indent since this line is coming after for
    // printf("%s", buffer2);
    putIndent(space, f2);
    fputs(buffer2, f2);
}

void copy(char *name1, char *name2, int space)
{
    char buffer[200];
    char buffer2[200];

    // For all lines:
    //    Create buffer string which suits to the definiton
    //    Put indent if requires (Before line of for loop, we should also put one line blank)
    //    Send result to the file
    sprintf(buffer, "for (int i=0; i<5; i++)\n");
    // printf("%s", buffer);
    fputs("\n", f2); // Head to the next line before putting for loop
    putIndent(space, f2);
    fputs(buffer, f2);

    sprintf(buffer2, "    %s[i] = %s[i];\n", name1, name2);
    // printf("%s", buffer2);
    putIndent(space, f2);
    fputs(buffer2, f2);
}

void initialize(char *name, char *value, int space)
{
    char buffer[200];
    char buffer2[200];

    // Get size of the variable name which is given in the arguments
    char size[20];
    getSizeFromAT(name, size);

    // For all lines:
    //    Create buffer string which suits to the definiton
    //    Put indent if requires (Before line of for loop, we should also put one line blank)
    //    Send result to the file

    sprintf(buffer, "for (int i=0; i<%s; i++)\n", size);
    // printf("%s", buffer);
    fputs("\n", f2); // Head to the next line before putting for loop
    putIndent(space, f2);
    fputs(buffer, f2);

    sprintf(buffer2, "    %s[i] = %s;\n", name, value);
    // printf("%s", buffer2);
    putIndent(space, f2);
    fputs(buffer2, f2);
}

void arithmetic(char *name1, char *name2, char *symbol, char *name3, int two_array, int special, int space)
{
    /*
     * All Arithmetic Operations except "$Y = 2 / $A" starts with a '$' sign after equal sign.
     * In order to consider different cases according to this difference, we are getting a new argument called special.
     */
    // Special = 1 : $C = 2 / $A;
    // Special = 0 : Other Arithmetic Operations

    // Two array argument gives us how many arrays are used after equal sign.
    // two_array = 1 : After Equal sign, there are two arrays. (Exp: "$Y = $A + $B")
    // two_array = 0 : After Equal sign, there is only one array. (Exp: "$Y = $A + 5")

    char buffer[200];
    char buffer2[200];

    // Get size of the variable name which is given in the arguments
    char size[5];
    clearString(size, 5);
    getSizeFromAT(name1, size);

    // For all lines:
    //    Create buffer string which suits to the definiton
    //    Put indent if requires (Before line of for loop, we should also put one line blank)
    //    Send result to the file
    sprintf(buffer, "for (int i=0; i<%s; i++)\n", size);
    // printf("%s", buffer);
    fputs("\n", f2);
    putIndent(space, f2);
    fputs(buffer, f2);

    if ((two_array == 1) && (special == 0)) // Two arrays after equal sign
    {
        sprintf(buffer2, "    %s[i] = %s[i] %c %s[i];\n", name1, name2, symbol[0], name3);
    }
    else if ((two_array == 0) && (special == 0)) // One array after equal sign
    {
        sprintf(buffer2, "    %s[i] = %s[i] %c %s;\n", name1, name2, symbol[0], name3);
    }
    else if (special == 1) // $C = 2 / $A;
    {
        sprintf(buffer2, "    %s[i] = %s %c %s[i];\n", name1, name2, symbol[0], name3);
    }

    // printf("%s", buffer2);
    putIndent(space, f2);
    fputs(buffer2, f2);
}

int main()
{
    // Get C code file with preprocessor commands as input
    // Set Expanded C code file as output
    f1 = fopen("deneme.c", "r");
    f2 = fopen("result.c", "w");

    // Read source code line by line
    while (fgets(code, sizeof(code), f1))
    {
        // printf("Code:%s\n", code);

        // Find indents if there are any exist
        int space = 0;
        if (code[0] == ' ')
        {
            while (code[space] == ' ')
            {
                space++;
            }
        }
        // printf("Space: %d\n\n", space);

        // If our line has preprocessor command
        if (code[space] == '$')
        {
            int i;
            // Start reading line one by line
            for (i = space; i < sizeof(code); i++)
            {
                // Declaration
                //**************************************************************
                if (strstr(code, "$dec"))
                {
                    // Skip char until we reach to first argument
                    while (code[i - 1] != '(')
                    {
                        i++;
                    }
                    // printf("Declaration:\n");

                    char name[10]; // array name
                    char size[5];  // array size
                    char type[10]; // int, float, etc.

                    int c = 0;

                    // Skip spaces between '(' and ',' chars if any before reaching to the first argument
                    while (code[i] == ',' || code[i] == ' ')
                    {
                        i++;
                    }

                    // Get name of the array
                    clearString(name, 10);
                    // printf("Name:");
                    //  Get name of the array
                    do
                    {
                        name[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ',' && code[i] != ' ');
                    // printf("\n");

                    // Skip spaces between '(' and ',' chars if any before reaching to the first argument
                    while (code[i] == ',' || code[i] == ' ')
                    {
                        i++;
                    }

                    // Re-use c variable to set variables
                    c = 0;

                    clearString(size, 5);
                    // printf("Size:");
                    //  Get size of the array
                    do
                    {
                        size[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ',' && code[i] != ' ');
                    // printf("\n");
                    //  Skip spaces between '(' and ',' chars if any before reaching to the first argument
                    while (code[i] == ',' || code[i] == ' ')
                    {
                        i++;
                    }

                    c = 0;

                    clearString(type, 10);
                    // printf("Type:");
                    //  Get type of the array
                    do
                    {
                        type[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ')' && code[i] != ' ');
                    // printf("\n");

                    // TODO: Call Function with the values we get from source code
                    declare(name, size, type, space);
                    break;
                }

                // Read
                //**************************************************************
                else if (strstr(code, "$read"))
                {
                    // Skip char until we reach to first argument
                    while (code[i - 1] != '(')
                    {
                        i++;
                    }
                    // printf("Read:\n");

                    char file_name[20];
                    char array[20];

                    int c = 0;

                    clearString(file_name, 20);
                    // printf("File:");
                    //  Get name of the file
                    do
                    {
                        file_name[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ',' && code[i] != ' ');
                    // printf("\n");
                    //  Skip spaces before array name (if any)
                    while (code[i] == ',' || code[i] == ' ')
                    {
                        i++;
                    }
                    c = 0;

                    clearString(array, 20);
                    // printf("Array:");
                    //  Get name of the array
                    do
                    {
                        array[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ')' && code[i] != ' ');
                    // printf("\n");

                    // TODO: Call Function with the values we get from source code
                    read(file_name, array, space);
                    break;
                }

                // Print
                //**************************************************************
                else if (strstr(code, "$print")) // Output
                {
                    while (code[i - 1] != '(')
                    {
                        i++;
                    }
                    // printf("Print:\n");

                    char array[20];

                    int c = 0;
                    clearString(array, 20);
                    // printf("Array:");
                    // Get name of the array
                    do
                    {
                        array[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;

                    } while (code[i] != ')' && code[i] != ' ');
                    // printf("\n");

                    // TODO: Call Function with the values we get from source code
                    print(array, space);
                    break;
                }

                else // Copy, Initialization, Arithmetic Operations
                {
                    i++;
                    char var[20];
                    clearString(var, 20);

                    // printf("Var:");
                    int c = 0;
                    // Get the array before the '=' sign
                    while (code[i] != ';')
                    {
                        if (code[i] == ' ' || code[i] == '=')
                        {
                            break;
                        }
                        var[c] = code[i];
                        // printf("%c", code[i]);
                        i++;
                        c++;
                    }

                    // Skip spaces and equal sign
                    while (code[i] == '=' || code[i] == ' ')
                    {
                        i++;
                    }

                    if (code[i] == '$') // If operation is Copy or Arithmetic Operations(except $Y = 2 / $A)
                    {
                        i++;
                        char v1[20];
                        int c = 0;

                        clearString(v1, 20);
                        // printf("\nVar1(if):");

                        // Get first variable of the operation
                        do
                        {
                            v1[c] = code[i];
                            // printf("%c", code[i]);
                            i++;
                            c++;
                        } while (code[i] != ' ' && code[i] != ';');
                        // printf("\n");

                        // Check if there exist a second argument (if not, it is Copy Operation)
                        if (code[i] == ';') // If arithmetic sign does not exist (Code end with ';')
                        {
                            // printf("Copy:\n");

                            // TODO: Call Function with the values we get from source code
                            copy(var, v1, space);
                            break;
                        }
                        else // Operation is Arithmetic Operations(except $Y = 2 / $A)
                        {
                            char symbol[1];
                            char v2[20];
                            int two_array = 0;

                            // Skip spaces before sign
                            while (code[i] == ' ')
                            {
                                i++;
                            }

                            // printf("Symbol(if):");
                            clearString(symbol, 1);

                            // Get arithmetic sign
                            symbol[0] = code[i];
                            // printf("%c", code[i]);
                            i++;
                            // printf("\n");

                            // Skip spaces
                            while (code[i] == ' ')
                            {
                                i++;
                            }

                            // If second argument has '$', after equal sign there are two arrays.
                            if (code[i] == '$')
                            {
                                two_array = 1;
                                i++;
                            }

                            c = 0;
                            clearString(v2, 20);

                            // Get second argument
                            // printf("Var2(if):");
                            do
                            {
                                v2[c] = code[i];
                                // printf("%c", code[i]);
                                i++;
                                c++;
                            } while (code[i] != ' ' && code[i] != ';');
                            // printf("\n");

                            // TODO: CALL FUNCTION
                            arithmetic(var, v1, symbol, v2, two_array, 0, space); // 0 : special
                            break;
                        }
                    }

                    else // Initialization or ($Y = 2 / $A)
                    {
                        int check_arith = 0;
                        int is_arith = 0;

                        // With using new variable we declared, go to the end of the line to find that
                        // if our line is arithmetic operation or initialization
                        while (code[i + check_arith] != ';')
                        {
                            if (code[i + check_arith] == '/') // Our line matches ($Y = 2 / $A)
                            {
                                is_arith = 1;
                                break;
                            }
                            check_arith++;
                        }

                        if (is_arith == 0) // Initialization
                        {
                            char value[20];
                            int c = 0;
                            // printf("\nInitialize to:");

                            clearString(value, 20);
                            // Get first argument after equal sign
                            while (code[i] != ';')
                            {
                                if (code[i] == ' ')
                                {
                                    break;
                                }

                                value[c] = code[i];
                                // printf("%c", code[i]);
                                i++;
                                c++;
                            }

                            // TODO: CALL FUNCTION
                            initialize(var, value, space);
                            break;
                        }

                        else // $Y = 2 / $A
                        {
                            char v1[20];
                            char symbol[1];
                            char v2[20];
                            int c = 0;

                            // printf("\nVar1:");
                            clearString(v1, 20);
                            // Get first argument after equal sign
                            do
                            {
                                v1[c] = code[i];
                                // printf("%c", code[i]);
                                i++;
                                c++;
                            } while (code[i] != ' ');

                            // printf("\n");

                            // Skip spaces
                            while (code[i] == ' ')
                            {
                                i++;
                            }

                            // printf("Symbol:");
                            clearString(symbol, 1);
                            // Get arithmetic sign
                            symbol[0] = code[i];
                            // printf("%c", code[i]);
                            i++;
                            // printf("\n");

                            // Skip spaces
                            while (code[i] == ' ')
                            {
                                i++;
                            }

                            i++;

                            // printf("Var2:");
                            c = 0;
                            clearString(v2, 20);
                            // Get second argument after equal sign
                            do
                            {
                                v2[c] = code[i];
                                // printf("%c", code[i]);
                                i++;
                                c++;
                            } while (code[i] != ' ' && code[i] != ';');

                            while (code[i] != ' ' && code[i] != ';')
                                ;

                            // printf("\n");

                            // TODO: CALL FUNCTION
                            arithmetic(var, v1, symbol, v2, 1, 1, space);
                            break;
                        }
                    }
                }
                printf("\n");
            }
        }
        else // Our line does not include preprocessor commands
        {
            if (code != " ")
            {
                fputs(code, f2); // Write line to the output code as same as input code
            }
        }
        clearString(code, 100); // Clear code to get new line
    }

    // Close Files
    fclose(f1);
    fclose(f2);

    return 0;
}
