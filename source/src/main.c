#include "result.h"
#include "scheme.h"
#include "share.h"
#include "error.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        error_msg("Many arguments");
        return 0;
    }

    char* cfg_name = argc == 0
        ? STD_CFG_NAME
        : argv[0];

    Scheme* scheme = scheme_create(cfg_name);

    scheme_solve(scheme);

    result_view(scheme->result);

    scheme_free(scheme);

    return 0;
}
