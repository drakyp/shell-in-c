#include <stdio.h>

int main() {

    printf("$ ");
    fflush(stdout);

    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);

    // take the input add the null character and return command not found
    input[strlen(input) - 1] = '\0';
    printf("%s: command not found\n", input);

    return 0;
}
