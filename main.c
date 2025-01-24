#include <stdio.h>

#include "get_value.h"

typedef struct
{
    char* name;
    int age;
} person;

int main()
{
    char* name = get_string(NULL, "What's your name? ");
    printf("Hello, %s\n", name);

    

    return 0;
}
