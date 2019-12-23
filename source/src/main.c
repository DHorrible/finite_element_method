#include "result.h"
#include "scheme.h"
#include "share.h"
#include "error.h"

int main(int argc, char* argv[]) {
    assert_msg(argc <= 1, "Many arguments");

    char* cfg_name = argc == 1
        ? STD_CFG_NAME
        : argv[0];

    Scheme* scheme = scheme_create(cfg_name);

    scheme_solve(scheme);
    
    result_view(scheme->result);

    scheme_free(scheme);

    return 0;
}
