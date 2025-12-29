#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include <stddef.h>

typedef enum {
    STR_SUCCESS = 0,
    STR_FAILURE = 1
} str_result;

typedef struct {
    char *buffer;
    size_t count;
    size_t capacity;
} str_t;

str_result str_set(str_t *str, const char *c_str);
str_result str_cat(str_t *dest, const char *c_str1, const char *c_str2);
str_result str_set_n(str_t *str, const char *c_str, size_t count);
str_result str_cat_n(str_t *dest, const char *c_str1, size_t count1, const char *c_str2, size_t count2);
str_result str_append_s(str_t *str, const char *c_str);
str_result str_append_s_n(str_t *str, const char *c_str, size_t count);
str_result str_append_c(str_t *str, char c);
str_result str_append_i(str_t *str, int i);
str_result str_append_d(str_t *str, double d);
void str_free(str_t *str);

#endif // STRING_TYPE_H

#ifdef STRING_TYPE_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

str_result str_set(str_t *str, const char *c_str)
{
    size_t count = strlen(c_str);
    size_t capacity = count + 1;
    if(capacity > str->capacity) {
        char *buf = realloc(str->buffer, capacity);
        if(!buf) return STR_FAILURE;
        str->buffer = buf;
        str->capacity = capacity;
    }

    char *ptr = str->buffer;
    while((*ptr++ = *c_str++));
    str->count = count;

    return STR_SUCCESS;
}

str_result str_set_n(str_t *str, const char *c_str, size_t count)
{
    size_t capacity = count + 1;
    if(capacity > str->capacity) {
        char *buf = realloc(str->buffer, capacity);
        if(!buf) return STR_FAILURE;
        str->buffer = buf;
        str->capacity = capacity;
    }

    char *ptr = str->buffer;
    for(size_t i = 0; i < count; ++i) *ptr++ = *c_str++;
    *ptr = '\0';
    str->count = count;

    return STR_SUCCESS;
}

str_result str_cat(str_t *dest, const char *c_str1, const char *c_str2)
{
    size_t count1 = strlen(c_str1);
    size_t count2 = strlen(c_str2);
    size_t capacity = count1 + count2 + 1;
    if(capacity > dest->capacity) {
        char *buf = realloc(dest->buffer, capacity);
        if(!buf) return STR_FAILURE;
        dest->buffer = buf;
        dest->capacity = capacity;
    }

    char c;
    char *ptr = dest->buffer;
    while((c = *c_str1++)) *ptr++ = c;
    while((*ptr++ = *c_str2++));
    dest->count = count1 + count2; 

    return STR_SUCCESS;
}

str_result str_cat_n(str_t *dest, const char *c_str1, size_t count1, const char *c_str2, size_t count2)
{
    size_t capacity = count1 + count2 + 1;
    if(capacity > dest->capacity) {
        char *buf = realloc(dest->buffer, capacity);
        if(!buf) return STR_FAILURE;
        dest->buffer = buf;
        dest->capacity = capacity;
    }

    char *ptr = dest->buffer;
    for(size_t i = 0; i < count1; ++i) *ptr++ = *c_str1++;
    for(size_t i = 0; i < count2; ++i) *ptr++ = *c_str2++;
    *ptr = '\0';
    dest->count = count1 + count2;

    return STR_SUCCESS;
}

str_result str_append_s(str_t *str, const char *c_str)
{
    size_t count = strlen(c_str);
    size_t new_cap = str->count + count + 1;
    if(new_cap > str->capacity) {
        char *buf = realloc(str->buffer, new_cap);
        if(!buf) return STR_FAILURE;
        str->buffer = buf;
        str->capacity = new_cap;
    }

    char *ptr = str->buffer;
    ptr += str->count;
    while((*ptr++ = *c_str++));
    str->count += count;

    return STR_SUCCESS;
}

str_result str_append_s_n(str_t *str, const char *c_str, size_t count)
{
    size_t new_cap = str->count + count + 1;
    if(new_cap > str->capacity) {
        char *buf = realloc(str->buffer, new_cap);
        if(!buf) return STR_FAILURE;
        str->buffer = buf;
        str->capacity = new_cap;
    }

    char *ptr = str->buffer;
    ptr += str->count;
    for(size_t i = 0; i < count; ++i) *ptr++ = *c_str++;
    *ptr = '\0';
    str->count += count;

    return STR_SUCCESS;
}

str_result str_append_c(str_t *str, char c)
{
    if(str->count >= str->capacity - 1) {
        char *buf = realloc(str->buffer, str->capacity * 2);
        if(!buf) return STR_FAILURE;
        str->buffer = buf;
        str->capacity *= 2;
    }

    str->buffer[str->count++] = c;
    str->buffer[str->count] = '\0';

    return STR_SUCCESS;
}

str_result str_append_i(str_t *str, int i)
{
    char buf[32] = {0};
    snprintf(buf, 32, "%d", i);

    return str_append_s(str, buf);
}

str_result str_append_d(str_t *str, double d)
{
    char buf[64] = {0};
    snprintf(buf, 64, "%f", d);

    return str_append_s(str, buf);
}

void str_free(str_t *str)
{
    free(str->buffer);
    str->buffer = NULL;
    str->count = 0;
    str->capacity = 0;
}

#endif // STRING_TYPE_IMPLEMENTATION
