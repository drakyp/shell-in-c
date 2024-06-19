#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

        if (!strcmp(input,"exit 0")) //because strcmp return 0 if the input is equal 
            exit(0);

        printf("%s: command not found\n", input);
    }


    return 0;
}
