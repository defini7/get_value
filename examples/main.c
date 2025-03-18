#include <stdio.h>

#include "../include/get_value.h"

int main()
{
    char c;

    do
    {
        char* name = get_string(NULL, "What's your name? ");
        printf("Hello, %s\n", name);
        free(name);
    }
    while ((c = get_char("Would you like to start again? (y/n) ")) == 'y' || c == 'Y');

    int n = get_int("Give me your age: ");

    printf("I guess your age is... %d!", n);
}
