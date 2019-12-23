#include "result.h"

void result_view(Result* result) {

}

void result_start_solve(Result* result) {

}

void result_stop_solve(Result* result) {

}

void result_free(Result* result) {
    free(result->sys_result);
    free(result);
}
