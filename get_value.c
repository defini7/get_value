#include "get_value.h"

void free_char_entry(char_entry* entry)
{
    while (entry != NULL)
    {
        // Get a next entry
        char_entry* next_entry = entry->next;

        // Free memory of the current entry...
        free(entry);

        // ... and set the next entry to it
        entry = next_entry;
    }
}

/*
* This function asks a user for a string
* and if the input string's length is larger
* than SIZE_MAX or if the user don't input something
* then the function returns NULL
*/
char* get_string(size_t* length, const char* format, ...)
{
    PRINTF(format);

    // That is the beginning of our linked list
    char_entry* head = ALLOCATE(char_entry);
    head->value = fgetc(stdin);
    head->next = NULL;

    if (head->value == EOF || head->value == '\r' || head->value == '\n')
    {
        // User hasn't provided any data
        free(head);
        return NULL;
    }

    // Now let's create a pointer to a currently read char value
    char_entry* entry;
    entry = head;

    size_t chars_read = 1;

    // While it's not a carriage return or a new line
    // we fetch characters from the stdin
    while (entry->value != '\n' && entry->value != '\r' && entry->value != EOF)
    {
        char_entry* new_entry = (char_entry*)malloc(sizeof(char_entry));

        // Read a character from the stdin 
        new_entry->value = fgetc(stdin);
        new_entry->next = NULL;
        
        // Go to the next iteration
        entry->next = new_entry;
        entry = new_entry;

        chars_read++;

        // User provided too much characters so there is no room for other ones
        if (chars_read > SIZE_MAX)
        {
            // Now let's clear our memory...
            free_char_entry(head);

            // ... and "gracefully" exit from the function
            return NULL;
        }
    }

    // Now let's copy everything into a dynamically allocated array
    char* output = (char*)malloc(chars_read);
    
    // Let's reuse old variables
    entry = head;

    for (size_t i = 0; i < chars_read; i++)
    {
        output[i] = entry->value;

        // Get a next entry
        char_entry* next_entry = entry->next;

        // Free memory of the current entry...
        free(entry);

        // ... and set the next entry to it
        entry = next_entry;
    }

    // Set trailing zero
    output[chars_read - 1] = '\0';

    if (length != NULL)
        *length = chars_read - 1;

    return output;
}

/*
* This function asks a user to provide a char value
* and if the user gives nothing or more than 1 character
* then the function returns CHAR_MAX
*/
char get_char(const char* format, ...)
{
    PRINTF(format);

    char* input = get_string(NULL, NULL);
    
    if (input == NULL || input[1] != '\0')
    {
        free(input);
        return CHAR_MAX;
    }

    char output = input[0];
    free(input);

    return output;
}

/*
* This function asks a user to provide a int value
* and if the user gives nothing or gives invalid int value
* then the function returns INT_MAX
*/
int get_int(const char* format, ...)
{
    PRINTF(format);

    size_t length;
    char* input = get_string(&length, NULL);

    if (input == NULL)
        return INT_MAX;

    int output = 0;
    int place = 1;

    for (int i = length - 1; i >= 0; i--)
    {
        if (!isdigit(input[i]))
        {
            free(input);
            return INT_MAX;
        }

        output += place * (int)(input[i] - '0');
        place *= 10;
    }

    free(input);
    return output;
}
