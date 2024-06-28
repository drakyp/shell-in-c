#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


const char *builtin[] = {"type", "echo", "exit", "pwd"};

int is_builtin(const char *command)
{
    for(int i = 0; i < sizeof(builtin) / sizeof(builtin[0]); i++)
    {
        if(!strcmp(command, builtin[i]))
            return 1;
    }
    return 0;
}

int main() {
    //repl
    while(1){

        printf("$ ");
        fflush(stdout);


        // Wait for user input
        char input[100];
        fgets(input, 100, stdin);

        // take the input add the null character and return command not found
        input[strlen(input) - 1] = '\0';
        char cop[100];
        strcpy( cop , input);

        //split into 2 part for echo
        char *command = strtok(cop, " ");
        char *arg = strtok(NULL, "");

        char *path = getenv("PATH");
        char pathcop[1000];
        strcpy (pathcop , path);
        char filename[200];
        char *p1 = strtok(pathcop , ":");
        


        if (!strcmp(input,"exit 0")) //because strcmp return 0 if the input is equal 
            exit(0);
        else if (!strcmp (command , "echo" )) // or just (!strcmp(input, "echo", strlen("echo")) == 0) strlen because we only want to compare the 1st 4 char with echo
            printf("%s\n", arg);// input + 5;continue;

        else if ( !strncmp(input, "type", strlen("type")))
        {
            
            int found = 0;

            if (is_builtin(input + 5))
            { 
                printf("%s is a shell builtin\n", input + 5);
                found = 1;
            }
            else{

                //parsing the path to see where does the command belong 
                while ( p1 != NULL)

                {
                    sprintf(filename, "%s/%s", p1 , input + 5);
                    if (!access(filename ,  F_OK))
                    {
                        printf("%s is %s\n", input + 5, filename);
                        found = 1;
                        break;

                }
                p1 = strtok(NULL, ":");

            }
        }


            if (!found)
                printf("%s: not found\n", input + 5);
        }
        else if (!strncmp(input, "pwd", strlen("pwd"))){
            //allocate space for the path of the current working directory 
            char cwd[1000];
            //calling the function in the if, thus if it work will be store into cwd else will return NULL
            if(getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n",cwd );
            else {
                perror(" couldn't find the pwd");
            }

        }
        else 
        {
            
           int found = 0;
            //check where is the fie located in the path
            while ( p1 != NULL){

                sprintf(filename, "%s/%s", p1, command);
                if (!access(filename, F_OK))
                {
                    found = 1;
                    break;
                }
                p1 = strtok(NULL , ":");
            }
            
            if(found){
                //stocking the arg into the array
                char *argv[10];
                argv[0] = command;
                int argc = 1;
                char *arg_t = strtok(arg, " ");
                while (arg_t != NULL && argc < 9){
                    argv[argc++] = arg_t;
                    arg_t = strtok(NULL, " ");
                }
                argv[argc] = NULL;

                //creating a new process to run the program
                pid_t pid = fork();
                
                //case if it is the child, child process is set to 0
                if (pid == 0){
                    execvp(command, argv);
                    perror("execvp failed");
                    exit(1);
                }
                else{
                    int status;
                    waitpid(pid , &status, 0);
                }
            }
            else {
                printf("%s: command not found\n", input);
            }
        }
    }


    return 0;
}
