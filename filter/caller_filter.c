#include <kern/kern_func.h>
#include "filters.h"

char target_execs[MAX_BLOCK_CALLER][MAX_CALLER_LEN];

int check_caller(const char *p) {
    int arrsize = sizeof(target_execs) / sizeof(target_execs[0]);
    //xprintf("checking through %d paths\n", arrsize);
    for (int i = 0; i < arrsize; i++) {
        if (target_execs[i][0] == 0) {
            break;
        }
	    //xprintf("checking %s vs %s\n", p, block_paths[i]);
        if (_strcmp(p, target_execs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void init_caller_filter(char **temp) {
    memcpy(target_execs, temp, sizeof(target_execs));
}