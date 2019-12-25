#ifndef METHOD_H
#define METHOD_H

#include "scheme.h"
#include "result.h"
#include "error.h"

void method_solve(Scheme* scheme);

static double** get_fin_elem_mtx(const Element* element);

#endif
