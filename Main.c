#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "Utility.h"
// Global constants
#define BUFSIZE 512

// Global variables
char buffer[BUFSIZE] = {0};
char *tokens[BUFSIZE];

/**Tokenizer function with a global buffer pointer
 * and a global tokens pointer array
 */
int tokenize(char *input, char *tokens[BUFSIZE])
{

    // Index var
    int i = 0;
    // Variable used for error checking
    char *ret;

    // For loop Initializes token pointer array to null for memory cleanup
    for (int i = 0; i < BUFSIZE; i++)
    {
        tokens[i] = NULL;
    }

    // Variable used for error checking
    ret = fgets(input, 512, stdin);
    // Checks for errors while reading std input
    if (ret == NULL)
    {
        if (errno != 0)
        {
            printf("error: %s\n", strerror(errno));
        }
        return (0);
    }

    // Splits first word from input and stores in p
    char *p = strtok(input, " ");

    // Splits subsequent words and stores them in token
    while (p != NULL)
    {
        tokens[i] = p;
        // printf("%s\n", p);
        p = strtok(NULL, " ");
        i = i + 1;
    }

    // Memory management
    free(p);

    // Used to Determine the number of splits (Called and used in main fucntion)
    return i;
}

int main(int argc, char *argv[])
{

    do
    {
        printf("Type words here:> ");

        // Number of words in the token pointer array
        int S_count = tokenize(buffer, tokens);

        // Displaying contents of token pointer array
        for (int i = 0; i < S_count; i++)
        {
            printf("Token %d = %s\n", i, tokens[i]);
        }

        printf("deciding what %s means\n", tokens[0]);

        if (strcmp(tokens[0], "echo") == 0)
        {
            printf("echoing: ");

            echo(buffer);
        }
        else if (strcmp(tokens[0], "clear") == 0)
        {
            printf("clearing:");
            clr();
        }

    } while (1);
}
