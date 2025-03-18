#include "../include/get_value.h"

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define PRINTF(format) { if (format != NULL) { va_list arguments; va_start(arguments, format); vprintf(format, arguments); va_end(arguments); } }

char* get_string(size_t* length, const char* format, ...)
{
    PRINTF(format);

    // That is the beginning of our linked list
    CharNode* head = (CharNode*)malloc(sizeof(CharNode));
    head->value = fgetc(stdin);
    head->next = NULL;

    if (head->value == EOF || head->value == '\r' || head->value == '\n')
    {
        // User hasn't provided any data
        free(head);
        return NULL;
    }

    // Now let's create a pointer to a currently read char value
    CharNode* entry;
    entry = head;

    size_t chars_read = 1;

    // Handles CR (Mac), LF (Linux) and CRLF (Windows)
    while (entry->value != '\n' && entry->value != '\r' && entry->value != EOF)
    {
        CharNode* new_entry = (CharNode*)malloc(sizeof(CharNode));

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
            while (head != NULL)
            {
                // Get a next entry
                CharNode* next_entry = head->next;

                // Free memory of the current entry...
                free(head);

                // ... and set the next entry to it
                head = next_entry;
            }

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
        CharNode* next_entry = entry->next;

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
