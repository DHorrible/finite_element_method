#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheme.h"
#include "share.h"
#include "error.h"

Scheme* scheme_create(const char* cfg_name) {
    Scheme* scheme = (Scheme*)malloc(sizeof(Scheme));
    
    FILE* cfg_file = fopen(cfg_name, "r");
    assert_msg(cfg_file != NULL, "Can't open config file");
    
    scheme_parse_conf(scheme, cfg_file);
    
    scheme->cfg_name = (char*)calloc(strlen(cfg_name) + 1, sizeof(char));
    memcpy(scheme->cfg_name, cfg_name, strlen(cfg_name) + 1);
    
    fclose(cfg_file);    
    //printf("%p\n", scheme);
    scheme->result = result_create(scheme);
    
    return scheme;
}

int scheme_solve(Scheme* scheme) {
    result_start_solve(scheme->result);
    
    // TODO: Solve

    result_stop_solve(scheme->result);
    return 0;
}

static int scheme_parse_conf(Scheme* scheme, FILE* cfg_file) {
    char* line = (char*)calloc(STD_MAX_LEN_CFG_STR, sizeof(char));
    
    int is_conn = 0;
    int is_first_conn = 1;

    int elem_len = 0;

    int last_conn_doff = DOFF_ALL;
    
    while (!feof(cfg_file)) {
        fgets(line, STD_MAX_LEN_CFG_STR, cfg_file);
        
        if (strstr(line, "elem:")) {
            is_conn = 0;
            scheme->elements_len = ++elem_len;
            scheme->elements = realloc(scheme->elements, scheme->elements_len);
            scheme->elements[scheme->elements_len - 1] = element_create();
            scheme->elements[scheme->elements_len - 1]->conn_start_doff = last_conn_doff;
        } else {
            if (is_conn) {
                if (strstr(line, "csrt")) {
                    if (is_first_conn) {
                        is_first_conn = 0;
                        scheme->elements[scheme->elements_len - 1]->conn_start_doff = get_cfg_int_val(line);
                    } else {
                        scheme->elements[scheme->elements_len - 1]->conn_finish_doff = get_cfg_int_val(line);
                    }
                    /*
                } else if (strstr(line, "fx")) {

                } else if (strstr(line, "fy")) {

                } else if (strstr(line, "fz")) {

                } else if (strstr(line, "mx")) {

                } else if (strstr(line, "my")) {

                } else if (strstr(line, "mz")) {

                }
                */
            } else if (strstr(line, "conn:")) {
                is_conn = 1;
            } else if (strstr(line, "l")) {
                is_conn = 0;
                scheme->elements[scheme->elements_len - 1]->length = get_cfg_double_val(line);
            } else if (strstr(line, "s")) {
                is_conn = 0;
                scheme->elements[scheme->elements_len - 1]->square = get_cfg_double_val(line);
            } else if (strstr(line, "e")) {
                is_conn = 0;
                scheme->elements[scheme->elements_len - 1]->hardness = get_cfg_double_val(line);
            }
        }
    
        }
    }
    free(line);

    return 0;
}

static int get_cfg_int_val(const char* str) {
    char* ptr = strchr(str, '=');
    
    assert_msg(ptr != NULL, "Config don't contanits '='");

    while (!isdigit(*ptr) && *ptr != '\n' && *ptr != EOF) {
        ++ptr;
    }

    assert_msg(isdigit(*ptr), "Config don't contanits int value");  

    return atoi(ptr);
}

static double get_cfg_double_val(const char* str) {
    char* ptr = strchr(str, '=');
    
    assert_msg(ptr != NULL, "Config don't contanits '='");

    while (!isdigit(*ptr) && *ptr != '\n' && *ptr != EOF) {
        ++ptr;
    }

    assert_msg(isdigit(*ptr), "Config don't contanits double value");
    
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
