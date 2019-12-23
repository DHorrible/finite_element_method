#ifndef RESULT_H
#define RESULT_H

#include <stdlib.h>
#include <stdio.h>

#include "element.h"

typedef struct Scheme Scheme;

typedef struct SystemResult {
    double time;
    int memory;
} SystemResult;

typedef struct Diff {
    Element* element;
    double doff1;
    double doff2;
    double doff3;
    double doff4;
    double doff5;
    double doff6;
} Diff;


typedef struct Result {
    Diff** diffs;
    int diffs_len;
    SystemResult* sys_result;
} Result;

Result* result_create(Scheme* scheme);

// For pretty output
void result_view(Result* result);

// For set system result
void result_start_solve(Result* result);
void result_stop_solve(Result* result);

// Free memory
void result_free(Result* result);

#endif
