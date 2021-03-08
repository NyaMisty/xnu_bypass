#include <kern/kern_func.h>

const char target_execs[][20] = {
    "allstars",
    "global",
};

int check_caller(const char *p) {
    int arrsize = sizeof(target_execs) / sizeof(target_execs[0]);
    //xprintf("checking through %d paths\n", arrsize);
    for (int i = 0; i < arrsize; i++) {
	    //xprintf("checking %s vs %s\n", p, block_paths[i]);
        if (_strcmp(p, target_execs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}