#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "Utility.h"
// Global constants
#define BUFSIZE 512

// Global variables
char buffer[BUFSIZE] = {0};
char *tokens[BUFSIZE];
char command[BUFSIZE];
FILE *commandSource;
char filePath[BUFSIZE];
// char *arguments[BUFSIZE];

char environmentVariables[2][BUFSIZE] = {0};
char currentDirectory[BUFSIZE] = {0};
char originDirectory[BUFSIZE] = {0};

/**Tokenizer function with a global buffer pointer
 * and a global tokens pointer array

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
*/

int main(int argc, char *argv[])
{
    getCurrentDir(currentDirectory, BUFSIZE);
    getCurrentDir(originDirectory, BUFSIZE);
    // strcpy(environmentVariables[0], "Current Directory: ");
    // strcpy(environmentVariables[1], "Origin: ");
    strcat(environmentVariables[0], currentDirectory);
    strcat(environmentVariables[1], originDirectory);

    printf("Welcome to the Shell\n");
    FILE *commandSource = NULL;
    // Parse the commands provided using argc and argv
    if (argc > 1)
    {
        commandSource = fopen(argv[1], "r");
        printf("Wellcome to the Shell again\n");
        if (commandSource == NULL)
        {
            printf("Error opening file...\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        commandSource = stdin;
    };

    do
    {
        if (commandSource == stdin)
        {
            printf("%s> ", environmentVariables[0]);
        }
        // Number of words in the token pointer array
        int S_count = tokenize(buffer, tokens, commandSource);
        if (S_count == -1)
        {
            quit();
        }
        // for testing the tokenizing/input
        /*
        // printf("buffer: %s\n", buffer);
        // // Displaying contents of token pointer array
        // for (int i = 0; i < S_count; i++)
        // {
        //     printf("Token %d = %s\n", i, tokens[i]);
        // }
        */

        strcpy(command, tokens[0]);
        // removes any newline characters from the first token, so single command lines have no trailing newline
        command[strcspn(command, "\n")] = 0;

        // printf("deciding what %s means\n", command);

        if (strcmp(command, "cd") == 0)
        {
            changeDir(environmentVariables[0], tokens[1]);
        }
        else if (strcmp(command, "clr") == 0)
        {
            // printf("clearing:");
            clr();
        }
        else if (strcmp(command, "dir") == 0)
        {
            // printf("clearing:");
            displayDir(environmentVariables[0]);
        }
        else if (strcmp(command, "environ") == 0)
        {
            // printf("clearing:");
            displayEnv(environmentVariables);
        }
        else if (strcmp(command, "echo") == 0)
        {
            echo(tokens, S_count); // MIGHT MAKE MORE SENSE TO KEEP THIS LOCAL BUT WHO KNOWS
            printf("\n");
        }
        else if (strcmp(command, "help") == 0)
        {
            // printf("clearing:");
            help();
        }
        else if (strcmp(command, "pause") == 0)
        {
            // printf("clearing:");
            shellPause();
        }

        else if (strcmp(command, "quit") == 0)
        {
            // printf("clearing:");
            quit();
        }
        else
        {
            // printf("%s is not a command, type help to see list of commands\n", command);
            if (inDir(environmentVariables[0], command) == -1)
            {
                printf("That is NOT a recognized command or program\n");
            }
            else
            {
                printf("That IS a recognized command or program\n");
                filePath[0] = '\0';
                strcat(filePath, environmentVariables[0]);
                strcat(filePath, "/");
                strcat(filePath, command);
                printf("opening program at file path:%s\n", filePath);
                // for (int i = 0; i < S_count; i++)
                // {
                //     arguments[i], tokens[i]
                // }
                pid_t childPID;
                childPID = fork();
                // fork successful
                // printf("%d\n", childPID);
                if (childPID >= 0)
                {
                    if (childPID != 0 && strcmp(tokens[S_count - 1], "&") != 0)
                    {
                        printf("Waiting For Program to Finish\n");
                        waitpid(childPID, 0, 0);
                    }
                    // child process
                    if (childPID == 0)
                    {
                        // printf("child about to execl\n");
                        execl(filePath, tokens);
                        if (errno != 0)
                        {
                            printf("error: %s\n", strerror(errno));
                        }
                    }
                }
                else
                {
                    puts("Fork failed");
                };
            };
        };

    } while (1);
}
