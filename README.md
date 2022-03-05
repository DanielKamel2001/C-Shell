# C-Shell myshell
A command-line interface shell developed in C for use with Linux Systems.
Developed for Operating Systems SOFE 3850U

### Lab Members:
Adris Azimi
Daniel Gohara Kamel
Jessica Leishman

## Description
myshell is a simple C shell capable of executing a variety of commands as outlined in the Command Section below. 

## Commands and Description
Command | Description
:----:|:----:
cd <path> | Changes the current working directory to the path specified in the argument. 
clr |  Clears the console/terminal window.
dir <directory> | Lists the contents of directory <directory>.
environ | Lists the environment strings.
echo <message> | Displays comment on the command line followed by a newline.
help | Displays all available commands in the shell.
pause | Pauses the shell until the 'Enter' key is pushed.
quit | Exits the shell.


## Using Makefile
A makefile includes the gcc command arguments needed to compile the shell program. The makefile is run by just typing in the “make” command.

## Running the Shell
First execute the makefile run, as outlined in the above section.
After this, simply type ./myshell in the command prompt to run the shell.

## Running the Shell with Input/Output Redirection
Input and output redirection allows the shell to determine what is to be replaced with the default standard input and output. 

For example, ‘< File’ would establish the mentioned file as standard input and ‘> File’ would establish the mentioned file as standard output.

## Piping Commands from Files
Invoking the shell with a text file as an argument will prompt the shell to interpret that text file as a series of commands and run them. 
A test text file Is provided try with "./MyShell commands.txt"

## Running programs
Invoking the name of an executable file will prompt the shell to execute that program, then return to normal operation after completion.
A test program is provided to test the shell invoking executables. This program will need to be compiled on the host machine.

## Running Background programs
Background execution allows for immediate use of the command prompt for further command execution, while the previously executed program is still running in parallel.

To achieve this, an ampersand (&) is appended to the end of a program invocation.
