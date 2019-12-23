#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheme.h"
#include "share.h"
#include "error.h"

Scheme* scheme_create(const char* cgf_name) {
    Scheme* scheme = (Scheme*)malloc(sizeof(Scheme));

    FILE* cfg_file = fopen(cgf_name, "r");
    assert_msg(!(cfg_file == NULL), "Can't open config file");

    scheme_parse_conf(scheme, cfg_file);

    fclose(cfg_file);

    return scheme;
}

int scheme_solve(Scheme* scheme) {
    result_start_solve(scheme->result);
    
    // TODO: Solve

    result_stop_solve(scheme->result);
    return 0;
}

static int scheme_parse_conf(Scheme* scheme, FILE* cfg_file) {
    char buff[STD_MAX_LEN_CFG_STR] = {0};
    
    int is_elem = 0;
    int is_conn = 0;
    int is_first_conn = 1;

    int elem_len = 0;

    int last_conn_doff = DOFF_ALL;

    while (feof(cfg_file)) {
        fgets(buff, STD_MAX_LEN_CFG_STR, cfg_file);
        if (is_elem) {
            if (is_conn) {
                if (strstr(buff, "csrt")) {
                    if (is_first_conn) {
                        is_first_conn = 0;
                        scheme->elements[scheme->elements_len - 1]->conn_start_doff = get_cfg_int_val(buff);
                    } else {
                        scheme->elements[scheme->elements_len - 1]->conn_finish_doff = get_cfg_int_val(buff);
                    }
                }
            } else if (strstr(buff, "conn:")) {
                is_conn = 1;
            } else if (strstr(buff, "l")) {
                scheme->elements[scheme->elements_len - 1]->length = get_cfg_double_val(buff);
            } else if (strstr(buff, "s")) {
                scheme->elements[scheme->elements_len - 1]->square = get_cfg_double_val(buff);
            } else if (strstr(buff, "e")) {
                scheme->elements[scheme->elements_len - 1]->hardness = get_cfg_double_val(buff);
            }
        } else {
            if (strstr(buff, "elem:")) {
                is_elem = 1;
                scheme->elements_len = ++elem_len;
                scheme->elements = realloc(scheme->elements, scheme->elements_len);
                scheme->elements[scheme->elements_len - 1] = element_create();
                scheme->elements[scheme->elements_len - 1]->conn_start_doff = last_conn_doff;
            }
        }
    }
    
    return 0;
}

static int get_cfg_int_val(const char* str) {
    char* ptr = strchr(str, '=');
    
    assert_msg(ptr != NULL, "Config don't contanits '='");

    while (!isdigit(*ptr) && *ptr != '\n' && *ptr != EOF) {
        ++ptr;
    }

    assert_msg(isdigit(ptr), "Config don't contanits int value");  

    return atoi(ptr);
}

static double get_cfg_double_val(const char* str) {
    char* ptr = strchr(str, '=');
    
    assert_msg(ptr != NULL, "Config don't contanits '='");

    while (!isdigit(*ptr) && *ptr != '\n' && *ptr != EOF) {
        ++ptr;
    }
    
    assert_msg(isdigit(ptr), "Config don't contanits double value");

    return atof(ptr);
}

void scheme_free(Scheme* scheme) {
    result_free(scheme->result);
    for (int i = 0; i < scheme->elements_len; i++) {
        free(scheme->elements[i]);
    }
    free(scheme->elements);
    free(scheme->cfg_name);
    free(scheme);
}
