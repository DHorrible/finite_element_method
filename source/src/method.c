#include "method.h"

void method_solve(Scheme* scheme) {
    duration_count();
    System* system = system_create(scheme);

    // TODO:

    scheme->result->sys_result->time = duration_count();
    system_free(system);
}

static void assembly(const Scheme* scheme, double** mtx) {
    for (int i = 0; i < scheme->elements_len; i++) {
        // TODO:
    }
}

static System* system_create(const Scheme* scheme) {
    // TODO:
    return NULL;
}

static void mtx_free(System* system) {
    free(system->vars);
    for (int i = 0; i < system->size; i++) {
        free(system->mtx[i]);
    }
    free(mtx);
    free(system);
}

static double duration_count() {
    static int k = 0;
    static struct timespec before, after;
    
    ++k;

    if (k % 2) {
        clock_gettime(CLOCK_REALTIME, &before);
        after.tv_nsec = after.tv_sec = 0;

        return 0.;
    } else {
        clock_gettime(CLOCK_REALTIME, &after);

        return (after.tv_sec - before.tv_sec) +
                (after.tv_nsec - before.tv_nsec) / 1e9;
    }
}
