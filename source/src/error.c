#include "error.h"

void assert_msg(int expr, const char* msg) {
    if (!expr) {
        error_msg(msg);
        assert(expr);
    }
}

void error_msg(const char* msg) {
    fprintf(stderr, "|ERROR|: %s\n", msg);
}

void info_msg(const char* msg) {
    fprintf(stderr, "|INFO|: %s\n", msg);
}
