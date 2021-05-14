#pragma once

#define MAX_BLOCK_PATH 300
#define MAX_PATH_LEN 256
#define MAX_BLOCK_CALLER 100
#define MAX_CALLER_LEN 50

extern int check_caller(const char *p);
extern int check_path(const char *p);

extern void init_caller_filter(char **temp);
extern void init_path_filter(char **temp);

extern int init_filters();