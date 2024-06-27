#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

const char *builtin[] = {"type", "echo", "exit"};

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

        

        


        if (!strcmp(input,"exit 0")) //because strcmp return 0 if the input is equal 
            exit(0);
        else if (!strcmp (command , "echo" )) // or just (!strcmp(input, "echo", strlen("echo")) == 0) strlen because we only want to compare the 1st 4 char with echo
            printf("%s\n", arg);// input + 5;continue;

        else if ( !strncmp(input, "type", strlen("type")))
        {
            char filename[200];
        int found = 0;
            char *p1 = strtok(pathcop , ":");

 if (is_builtin(input + 5))
        { printf("%s is a shell builtin\n", input + 5);
        found = 1;
        }
            else{

                    
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
        {
            printf("%s: not found\n", input + 5);
        }
    }
        else 
        printf("%s: command not found\n", input);
    }


    return 0;
}
