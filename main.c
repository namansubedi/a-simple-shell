/*
COSC 4302: Introduction to Operating Systems
Group Project: Simple Shell

Group 27
Naman Subedi (L20615286)
Vijender Reddy Sirrapu (L20610709)

Starting with the code in Section 2.4, design and implement a simple, interactive shell pro-gram that prompts the user for a command,
parses the command, and then executes it with a child process. In your solution you are required to use execv ( ) instead of execvp ( ),
which means that you will have to read the PATH environment variable, then search each directory in the PATH for the command file name
that appears on the command line.

This program compiles and executes successfully.
*/

//imports
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

//define constants
#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARGS_LEN 16
#define MAX_PATHS 64
#define MAX_PATH_LEN 96
#define WHITESPACE " .,\t\n"

#ifndef NULL
#define NULL
#endif

struct command_t
{
    char *name;
    int argc;
    char *argv[MAX_ARGS];
};

//design and print a default prompt string. 
void printPrompt()
{
    printf("\nGroupShell$");
}

//get the command line 
void readCommand(char *buffer)
{
    gets(buffer);
}

//parse a command from standard input and creates a command struct.
int parseCommand(char *cLine, struct command_t *cmd)
{
    int argc;

    char **clPtr;

    clPtr = &cLine; // cLine is the command line

    argc = 0;

    cmd->argv[argc] = (char *)malloc(MAX_ARGS_LEN);
    //Fill argv[] 
    while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL)
    {
        cmd->argv[++argc] = (char *)malloc(MAX_ARGS_LEN);
    }
    // set the command name and argc 
    cmd->argc = argc - 1;
    cmd->name = (char *)malloc(sizeof(cmd->argv[0]));

    strcpy(cmd->name, cmd->argv[0]);

    return 1;
}

/*
This function reads the PATH variable for the environment and builds
array of all directories in the PATH
reads the PATH variable for the environment variable
*/

int parsePath(char *dirs[])
{
    // then builds an array of all directories in the PATH
    int i = 0;
    char *pathEnvVar;
    char *thePath;

    for (i = 0; i < MAX_ARGS; i++)
    {
        dirs[i] = NULL;
    }
    pathEnvVar = (char *)getenv("PATH");
    thePath = (char *)malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

    for (i = 0; i < MAX_PATHS; i++)
    {
        dirs[i] = strsep(&thePath, ":");
        if (dirs[i] == NULL)
            break;
    }

    return 0;
}

/*
This function searches the directories identified by the dir argument to see if argv[0]
(the file name) appears there. Allocate a new string, place the full path name in it,
then return the string.
*/

char *lookupPath(char **argv, char **dirs)
{
    int i;
    char pName[MAX_PATH_LEN];
    char *result;
    char *tmp = (char *)malloc(MAX_PATH_LEN);

    if (*argv[0] == '/')
    { // if file name is an absolute path
        result = argv[0];
        return result;
    }
    for (i = 0; i < MAX_PATHS; i++)
    {
        if (dirs[i] == NULL)
        {
            break;
        }
        strcpy(tmp, dirs[i]); // Copy dirs[i] to tmp.  
        strcat(tmp, "/");     // Append no more than N characters from SRC onto tmp.  
        strcat(tmp, argv[0]);
        strcpy(pName, tmp);

        if (access(pName, 0) == 0)
        { // Test for existence.  
            result = tmp;
            return result;
        }
    }
    fprintf(stderr, "%s: command not found \n", argv[0]); // file name not found in any path variable
    return NULL;
}

//main method
int main()
{

    int chPID;
    char *pathv[MAX_PATHS];
    char cmdLine[LINE_LEN];
    struct command_t command;
    parsePath(pathv);
    while (1)
    {
        printPrompt();
        readCommand(cmdLine);
        if (strcmp(cmdLine, "exit") == 0)
            exit(0);
        else
        {
            if (strlen(cmdLine) > 0)
            {
                parseCommand(cmdLine, &command);
                command.name = lookupPath(command.argv, pathv); // gives the full pathname of the file
                if (command.name == NULL)
                {
                    fprintf(stderr, "command \"%s\" unknown", command.name);
                    continue;
                }
                else
                {
                    if ((chPID = fork()) == 0)
                    { // creates child to execute commands
                        execv(command.name, command.argv);
                        exit(0);
                    }
                    else
                        wait(NULL); // wait for the child process to terminate.
                }
                if (command.name != NULL)
                    free(command.name);
            }
        }
    }
    return 0;
}