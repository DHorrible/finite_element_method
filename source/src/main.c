#include "result.h"
#include "scheme.h"
#include "share.h"
#include "error.h"
#include "method.h"

int main(int argc, char* argv[]) {
    assert_msg(argc <= 1, "Many arguments");

    char* cfg_name = argc == 1
        ? STD_CFG_NAME
        : argv[0];

    Scheme* scheme = scheme_create(cfg_name);

    method_solve(scheme);
    
    result_view(scheme->result);
    /*
    for (int i = 0; i < scheme->elements_len; i++) {
        printf(
            "element %d:\n%lf\n%lf\n%lf\n%lf\n",
            i + 1,
            scheme->elements[i]->l,
            scheme->elements[i]->a,
            scheme->elements[i]->b,
            scheme->elements[i]->e);

        printf(
            "\tstart:\n\t\t%x\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n",
            scheme->elements[i]->conn_start->doff,
            scheme->elements[i]->conn_start->fx,
            scheme->elements[i]->conn_start->fy,
            scheme->elements[i]->conn_start->fz,
            scheme->elements[i]->conn_start->mx,
            scheme->elements[i]->conn_start->my,
            scheme->elements[i]->conn_start->mz);

        printf(
            "\tfinish:\n\t\t%x\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n\t\t%lf\n",
            scheme->elements[i]->conn_finish->doff,
            scheme->elements[i]->conn_finish->fx,
            scheme->elements[i]->conn_finish->fy,
            scheme->elements[i]->conn_finish->fz,
            scheme->elements[i]->conn_finish->mx,
            scheme->elements[i]->conn_finish->my,
            scheme->elements[i]->conn_finish->mz);
            
    }
    */
    //scheme_free(scheme);

    return 0;
}
