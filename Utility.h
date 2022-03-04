
#ifndef UTILITY_H_
#define UTILITY_H_

#define BUFSIZE 512
// #define BUFF_LENGTH ; // need to add whatever adris uses for the buffer here
// Function headers

extern char buffer[];
extern char *tokens[];
// responsible for tokenizing string input to understand it
extern int tokenize(char *input, char *tokens[BUFSIZE]);

// changes the directory
extern void changeDir(char *pwd, char *newDirPath);
/* Change the current default directory to
<directory>. If the <directory> argument is not present, report
the current directory. If the directory does not exist an appropriate
error should be reported. This command should also change the PWD
environment variable. */

// clears screen
extern void clr();
clrscr(); // from my understanding this is a c console call that clears screen
// alternatively: system("clear");

// echo message back with a newline at the end
extern void echo(char *msg[], int count);

// displays user manual using "more"
extern void help();
// manually print all the commands available in our shell

// displays the contents of the current directory
extern void displayDir(char *path);

// lists all then environment strings
extern void displayEnv(char env[][BUFSIZE]);

// pauses the shell
extern void pause();

// quits the shell
extern void quit();

// obtains the current working directory
extern void getCurrentDir(char *pwd, int bufferSize);

/*  Not really sure how to include this requirement, i think this might be able to include in getCurrentDir?
The shell environment should contain shell=<pathname>/myshell
where <pathname>/myshell is the full path for the shell executable
(not a hardwired path back to your directory, but the one from which
it was executed). */
#endif