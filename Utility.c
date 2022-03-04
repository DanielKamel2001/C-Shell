#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h> // ONLY WORKS ON POSIX SYS, use https://github.com/tronkko/dirent for Windows
#include "Utility.h"

int tokenize(char *input, char *tokens[BUFSIZE], FILE *source)
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
    ret = fgets(input, 512, source);

    // Checks for errors while reading std input

    if (ret == NULL)
    {
        if (errno != 0)
        {
            printf("error: %s\n", strerror(errno));
        }
        return (-1);
    }

    // removes any new line characters for cleanliness
    input[strcspn(input, "\n")] = 0;
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

// changes the directory
void changeDir(char *pwd, char *newDirPath)
{
    /* Change the current default directory to
    <directory>. If the <directory> argument is not present, report
    the current directory. If the directory does not exist an appropriate
    error should be reported. This command should also change the PWD
    environment variable. */

    int changeStat = chdir(newDirPath); // returns 0 on success, -1 on error

    // verify that they actually passed a new path to change to
    if (strcmp(newDirPath, "") != 0)
    {

        // if the attempt at changing the directory is success
        if (changeStat == 0)
        {
            getCurrentDir(pwd, BUFSIZE); // obtains the current working directory
        }
        else
        {
            printf("Directory change to ");
            printf("%s", newDirPath);
            printf(" was unsuccessful! No such path exists!");
        }
    }
}

// clears screen
void clr()
{
    // clrscr(); // from my understanding this is a c console call that clears screen
    // alternatively: system("clear")
    system("clear");
}

// echo message back with a newline at the end
void echo(char *msg[], int count)
{
    if (count <= 1)
    {
        printf("please pass what you would like to echo!\n");
        return;
    }
    for (int i = 1; i < count; i++)
    {
        // tokens were delimted by a space so this is fine
        printf("%s ", msg[i]);
    }
    printf("\n");
}

// displays user manual using "more"
void help()
{
    // manually print all the commands available in our shell
    printf("Commands available within this shell:\n");
    printf("cd <path>: \t\t changes the current working directory to the path specified in the argument.\n");
    printf("clr: \t\t\t clears the console/terminal window.\n");
    printf("echo <message>: \t Displays comment on the command line followed by a newline.\n");
    printf("help: \t\t\t dispays all available commands in the shell (you're here right now!)\n");
    printf("dir <directory>: \t Lists the contents of directory <directory>\n");
    printf("environ: \t\t Lists the environment strings.\n");
    printf("pause: \t\t\t Pauses the shell until the 'Enter' key is pushed\n");
    printf("quit: \t\t\t Exits the shell\n");
}

// displays the contents of the directory specified

void displayDir(char *path)
{
    // structure studied from https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
    struct dirent *dir;
    DIR *d = NULL;
    if (strcmp(path, "") == 0)
    {
        d = opendir(".");
    }
    else
    {
        d = opendir(path);
    }

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
    }
    else
    {
        printf("Directory could not be found");
    }
    closedir(d);
}

// lists all then environment strings
void displayEnv(char env[][BUFSIZE])
{
    printf("%s\n%s\n", env[0], env[1]);
}

// pauses the shell
void pause()
{
    // create a loop for the shell to get stuck in until enter pressed
    char key;
    printf("The shell has been paused. Press ENTER to resume opertation");
    key = (char)getchar();

    while (key != '\n')
    {
        key = (char)getchar();
    }
}

// quits the shell
void quit()
{
    printf("Terminating the shell...");
    exit(0);
}

// obtains the current working directory
void getCurrentDir(char *pwd, int bufferSize)
{
    // return a null-terminated string containing an absolute pathname that is the current working directory of thecalling process.
    getcwd(pwd, bufferSize);
}
/*  Not really sure how to include this requirement, i think this might be able to include in getCurrentDir?
The shell environment should contain shell=<pathname>/myshell
where <pathname>/myshell is the full path for the shell executable
(not a hardwired path back to your directory, but the one from which
it was executed). */