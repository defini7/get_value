#ifndef _GET_VALUE_H_
#define _GET_VALUE_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

#define ALLOCATE(t) (t*)malloc(sizeof(t))
#define PRINTF(format) { if (format != NULL) { va_list arguments; va_start(arguments, format); vprintf(format, arguments); va_end(arguments); } }

typedef struct _char_entry
{
    char value;
    struct _char_entry* next;
} char_entry;

void free_char_entry(char_entry* entry);

char* get_string(size_t* length ,const char* format, ...);
char get_char(const char* format, ...);
int get_int(const char* format, ...);

#endif
