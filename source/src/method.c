#include "method.h"

void method_solve(Scheme* scheme) {
    result_start_solve(scheme->result);
    
    // TODO: Solve

    result_stop_solve(scheme->result);
}

static double** get_fin_elem_mtx(const Element* element) {
    // TODO:
    return NULL;
}
