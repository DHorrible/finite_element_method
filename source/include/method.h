#ifndef METHOD_H
#define METHOD_H

#include <time.h>

#include "scheme.h"
#include "result.h"
#include "error.h"

typedef struct System {
    double** vars;
    double** mtx;
    unsigned size;
} System;

void method_solve(Scheme* scheme);

static void assembly(const Scheme* scheme, double** mtx);

static double duration_count();

static void system_create(const Scheme* scheme);
static void system_free(System* system);

#endif
