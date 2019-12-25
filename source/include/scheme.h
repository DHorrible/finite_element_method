#ifndef SCHEME_H
#define SCHEME_H

#include <stdio.h>
#include <ctype.h>

#include "element.h"
#include "result.h"
#include "error.h"

typedef struct Scheme {
    char* cfg_name;
    Element** elements;
    int elements_len;
    Result* result;
} Scheme;

Scheme* scheme_create(const char* cgf_name);

// Free memory
void scheme_free(Scheme* scheme);

// Parse config file
static int scheme_parse_conf(Scheme* scheme, FILE* cfg_file);
static int get_cfg_int_val(const char* str);
static double get_cfg_double_val(const char* str);
static int get_cfg_csrt_arr(char** ptr);

#endif