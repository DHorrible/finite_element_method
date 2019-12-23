#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <assert.h>

void assert_msg(int expr, const char* msg);

void error_msg(const char* msg);
void info_msg(const char* msg);

#endif
