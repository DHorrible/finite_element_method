#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheme.h"
#include "share.h"
#include "error.h"

Scheme* scheme_create(const char* cfg_name) {
    Scheme* scheme = (Scheme*)malloc(sizeof(Scheme));
    scheme->elements = NULL;
    
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

static int scheme_parse_conf(Scheme* scheme, FILE* cfg_file) {
    char* line = (char*)calloc(STD_MAX_LEN_CFG_STR, sizeof(char));
    
    int is_conn = 0;
    int is_first_conn = 1;

    int was_l = 1;
    int was_a = 1;
    int was_b = 1;
    int was_e = 1;

    int elem_len = 0;

    unsigned general_doff = DOFF_ALL;

    while (!feof(cfg_file)) {
        fgets(line, STD_MAX_LEN_CFG_STR, cfg_file);
        if (strstr(line, "elem:")) {
            assert_msg(
                was_l && was_a && was_b && was_e, 
                "Not all properety of element");
            was_l = was_a = was_b = was_e = 0;
            is_conn = 0;
            scheme->elements_len = ++elem_len;
            scheme->elements = (Element**)realloc(scheme->elements, scheme->elements_len * sizeof(Element*));
            scheme->elements[scheme->elements_len - 1] = element_create();
            if (elem_len > 1) {
                scheme->elements[scheme->elements_len - 1]->conn_start = scheme->elements[scheme->elements_len - 2]->conn_finish;
                if (elem_len == 2) {
                    scheme->elements[0]->conn_finish = scheme->elements[1]->conn_start; 
                }
            }
        } else {
            if (strstr(line, "csrt")) {
                char* ptr = line;
                while (ptr != NULL) {
                    unsigned csrt = get_cfg_csrt_arr(&ptr);
                    if (is_first_conn) {
                        update_doff(scheme->elements[scheme->elements_len - 1]->conn_start, csrt);
                    } else {
                        update_doff(scheme->elements[scheme->elements_len - 1]->conn_finish, csrt);
                    }
                    general_doff &= csrt;
                }
            } else if (strstr(line, "fx")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->fx = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->fx = get_cfg_double_val(line);
                }
            } else if (strstr(line, "fy")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->fy = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->fy = get_cfg_double_val(line);
                }
            } else if (strstr(line, "fz")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->fz = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->fz = get_cfg_double_val(line);
                }
            } else if (strstr(line, "mx")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->mx = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->mx = get_cfg_double_val(line);
                }
            } else if (strstr(line, "my")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->my = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->my = get_cfg_double_val(line);
                }
            } else if (strstr(line, "mz")) {
                if (is_first_conn) {
                    scheme->elements[scheme->elements_len - 1]->conn_start->mz = get_cfg_double_val(line);
                } else {
                    scheme->elements[scheme->elements_len - 1]->conn_finish->mz = get_cfg_double_val(line);
                }    
            } else if (strstr(line, "l")) {
                is_conn = 0;
                was_l = 1;
                scheme->elements[scheme->elements_len - 1]->l = get_cfg_double_val(line);
            } else if (strstr(line, "a")) {
                is_conn = 0;
                was_a = 1;
                scheme->elements[scheme->elements_len - 1]->a = get_cfg_double_val(line);
            } else if (strstr(line, "b")) {
                is_conn = 0;
                was_b = 1;
                scheme->elements[scheme->elements_len - 1]->b = get_cfg_double_val(line);
            } else if (strstr(line, "e")) {
                is_conn = 0;
                was_e = 1;
                scheme->elements[scheme->elements_len - 1]->e = get_cfg_double_val(line);
            } else if (strstr(line, "conn:")) {
                is_first_conn = is_conn && is_first_conn ? 0 : is_first_conn;
                is_conn = 1;
            }
        }
    }

    assert_msg(general_doff == 0, "Can't solve");

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

static int get_cfg_csrt_arr(char** ptr) {
    static int first_call = 1;
    if (first_call) {
        *ptr = strchr(*ptr, '=');
        ++(*ptr);
        first_call = 0;
    }

    while (!isalnum(**ptr) && **ptr != '\n' && **ptr != EOF) {
        ++(*ptr);
    }

    if (!isalnum(**ptr)) {
        first_call = 1;
        *ptr = NULL;
        return CSTR_NONE;
    }

    switch (**ptr) {
        case '1':
            ++(*ptr);
            return CSTR_ALL;
        case 'x':
            if (*(*ptr + 1) == 'y') {
                *ptr += 2;
                return CSTR6;
            } else if (*(*ptr + 1) == 'z') {
                *ptr += 2;
                return CSTR5;
            } else {
                assert_msg(
                    isspace(*(*ptr + 1)) || *(*ptr + 1) == '\n' || *(*ptr + 1) == EOF, 
                    "Error cstr type in configuration");
            }
            ++(*ptr);
            return CSTR1;
        case 'y':
            if (*(*ptr + 1) == 'x') {
                *ptr += 2;
                return CSTR6;
            } else if (*(*ptr + 1) == 'z') {
                *ptr += 2;
                return CSTR4;
            } else {
                assert_msg(
                    isspace(*(*ptr + 1)) || *(*ptr + 1) == '\n' || *(*ptr + 1) == EOF, 
                    "Error cstr type in configuration");
            }
            ++(*ptr);
            return CSTR2;
        case 'z':
            if (*(*ptr + 1) == 'x') {
                *ptr += 2;
                return CSTR5;
            } else if (*(*ptr + 1) == 'y') {
                *ptr += 2;
                return CSTR4;
            } else {
                assert_msg(
                    isspace(*(*ptr + 1)) || *(*ptr + 1) == '\n' || *(*ptr + 1) == EOF, 
                    "Error cstr type in configuration");
            }
            ++(*ptr);
            return CSTR3;
        default:
            ++(*ptr);
            return CSTR_NONE;
    }
}

void scheme_free(Scheme* scheme) {
    for (int i = 0; i < scheme->elements_len; i++) {
        element_free(scheme->elements[i]);
    }
    free(scheme->elements);
    result_free(scheme->result);
    free(scheme->cfg_name);
    free(scheme);
}
