#include "result.h"

#include "scheme.h"

Result* result_create(Scheme* scheme) {
    Result* result = (Result*)malloc(sizeof(Result));

    result->sys_result = (SystemResult*)malloc(sizeof(SystemResult*));
    result->sys_result->memory = 0;
    result->sys_result->time = 0.;

    result->diffs = (Diff**)malloc(scheme->elements_len * sizeof(Diff));
    result->diffs_len = scheme->elements_len;
    for (int i = 0; i < result->diffs_len; i++) {
        result->diffs[i]->element = scheme->elements[i];
        result->diffs[i]->doff1 = 0;
        result->diffs[i]->doff2 = 0;
        result->diffs[i]->doff3 = 0;
        result->diffs[i]->doff4 = 0;
        result->diffs[i]->doff5 = 0;
        result->diffs[i]->doff6 = 0;
    }

    scheme->result = result;

    return result;
}

void result_view(Result* result) {
    //printf("%p", result);
    /*
    for (int i = 0; i < result->diffs_len; i++) {
        printf(
            "Element %d:\n\tUx = %lf\n\tUy = %lf\n\tUz = %lf\n\tMx = %lf\n\tMy = %lf\n\tMz = %lf\n",
            i + 1,
            result->diffs[i]->doff1,
            result->diffs[i]->doff2,
            result->diffs[i]->doff3,
            result->diffs[i]->doff4,
            result->diffs[i]->doff5,
            result->diffs[i]->doff6);
    }
    */

//    printf(
//        "Time - %lf\tMemory = %d",
//        result->sys_result->time,
//        result->sys_result->memory);
}

void result_start_solve(Result* result) {
    // TODO:
}

void result_stop_solve(Result* result) {
    // TODO:
}

void result_free(Result* result) {
    free(result->sys_result);
    free(result);
}
