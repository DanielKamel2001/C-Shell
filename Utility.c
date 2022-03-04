#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"

int tokenizer();

// changes the directory
void changeDir(char *pwd, char *newDirPath)
{
    /* Change the current default directory to
    <directory>. If the <directory> argument is not present, report
    the current directory. If the directory does not exist an appropriate
    error should be reported. This command should also change the PWD
    environment variable. */
    int changeStat = chdir(newDirPath);

    // verify that they actually passed a new path to change to
    if (strcmp(newDirPath, "") != 0)
    {

        if (changeStat == 0)
        {
            getCurrentDir(pwd, BUFSIZE);
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
void echo(char *msg)
{
    printf("%s\n", msg);
}

// displays user manual using "more"
void help()
{
    // manually print all the commands available in our shell
    printf("Commands available within this shell:\n");
    printf("cd <path>: \t\t changes the current working directory to the path specified in the argument.\n");
    printf("clr: \t\t\t clears the console/terminal window.\n");
    printf("echo <message>: \t\t Displays comment on the command line followed by a newline.\n");
    printf("help: \t\t\t dispays all available commands in the shell (you're here right now!)\n");
    printf("dir <directory>: \t\t Lists the contents of directory <directory>\n");
    printf("environ: \t\t\t Lists the environment strings.\n");
    printf("pause: \t\t\t Pauses the shell until the 'Enter' key is pushed");
    printf("quit: \t\t\t Exits the shell");
}

// displays the contents of the directory specified
void displayDir(char *path)
{
}

// lists all then environment strings
void displayEnv()
{
}

// pauses the shell
void pause()
{
    // create a loop for the shell to get stuck in until enter pressed
    char key;
    printf("The shell has been paused. Press ENTER to resume opertation");
    key = (char)getchar();

    while (key != "\n")
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