#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFERSIZE 256

//Function prototypes
int processinput(char *input); //Processing the input
int parseinput(char *input, char **args); //Parsing the input into a list of arguments
int execcommand(char **args); //Executing the command
int execute(char **args); //Executing the command and handling errors
int builtin_command(char **args); //Handling the built-in commands

int main(int argc, char *argv[])
{
    char *input; //Used to store the input
    size_t inputsize = BUFFERSIZE; //Used to set the size of the buffer
    int status; //Used to store the status code of the processes
    
    //Check if the program is running in interactive mode
    if (isatty(fileno(stdin)))
    {
        //If the program is running in interactive mode,
        //continuously prompt the user for input
        while (1) 
        {
            printf("unix>");
            input = (char *)malloc(BUFFERSIZE * sizeof(char));
            getline(&input, &inputsize, stdin);
            status = processinput(input);
            
            //Free the allocated memory
            free(input);
            
            //If the user wants to exit, break from the loop
            if (status == 0)
                break;
        }
    }
    else
    {
        //If the program is running in non-interactive mode,
        //read the input from stdin
        while (1)
        {
            input = (char *)malloc(BUFFERSIZE * sizeof(char));
            getline(&input, &inputsize, stdin);
            status = processinput(input);
            
            //Free the allocated memory
            free(input);
            
            //If the user wants to exit, break from the loop
            if (status == 0)
                break;
        }
    }
    
    return 0;
}

//Process the input
int processinput(char *input)
{
    int status; //Used to store the status code of the processes
    char **args; //Used to store the list of arguments
    
    //Parse the input into a list of arguments
    status = parseinput(input, args);
    
    //Execute the command
    status = execcommand(args);
    
    //Return the status code of the executed process
    return status;
}

//Parse the input into a list of arguments
int parseinput(char *input, char **args)
{
    int i = 0; //Used as an index
    
    //Split the input into a list of arguments
    args[i] = strtok(input, " \t\r\n\a");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " \t\r\n\a");
    }
    
    return 0;
}

//Execute the command
int execcommand(char **args)
{
    int status; //Used to store the status code of the processes
    
    //Execute the command and handle errors
    status = execute(args);
    
    return status;
}

//Execute the command and handle errors
int execute(char **args)
{
    int status; //Used to store the status code of the processes
    
    //Check if the command is a built-in command
    status = builtin_command(args);
    if (status != 0)
    {
        //If the command is not a built-in command,
        //fork a new process to execute the command
        pid_t pid, wpid;
        pid = fork();
        
        //Check if the fork was successful
        if (pid == 0)
        {
            //If the fork was successful,
            //execute the command
            if (execvp(args[0], args) == -1)
            {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            //If the fork failed,
            //print an error message
            perror("Error");
        }
        else
        {
            //Wait for the new process to finish
            do
            {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    
    return status;
}

//Handle the built-in commands
int builtin_command(char **args)
{
    int status = 1; //Used to store the status code of the processes
    
    //Check if the command is the exit built-in
    if (strcmp(args[0], "exit") == 0)
    {
        //If the command is the exit built-in,
        //set the status code to 0 and exit
        status = 0;
        exit(EXIT_SUCCESS);
    }
    //Check if the command is the env built-in
    else if (strcmp(args[0], "env") == 0)
    {
        //If the command is the env built-in,
        //print the current environment
        status = 0;
        char **env = environ;
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
    
    return status;
}
