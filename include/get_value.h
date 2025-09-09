#ifndef GET_VALUE_H
#define GET_VALUE_H

/* !!! NOTE !!!
* You must free every char* returned from the get_string function
* because framework does not do it for you
*/

#include <stdlib.h>

typedef struct CharNode
{
    char value;
    struct CharNode* next;
} CharNode;

/*
* This function asks a user to provide a string
* and if the input string's length is larger
* than SIZE_MAX or if the user hasn't provided any input
* the function returns NULL
*/
char* get_string(size_t* length, const char* format, ...);

/*
* This function asks a user to provide a char value
* and if the user gives nothing or more than 1 character
* then the function returns CHAR_MAX
*/
char get_char(const char* format, ...);

/*
* This function asks a user to provide an integer value
* and if the user gives nothing or gives an invalid integer value
* then the function returns INT_MAX
*/
int get_int(const char* format, ...);

#endif // GET_VALUE_H
