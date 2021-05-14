#include <kern/kern_func.h>
#include "filters.h"

char block_paths[MAX_BLOCK_PATH][MAX_PATH_LEN];

int check_path(const char *p) {
    int arrsize = sizeof(block_paths) / sizeof(block_paths[0]);
    //xprintf("checking through %d paths\n", arrsize);
    for (int i = 0; i < arrsize; i++) {
        if (block_paths[i][0] == 0) {
            break;
        }
	    //xprintf("checking %s vs %s\n", p, block_paths[i]);
        if (_strncmp(p, block_paths[i], _strlen(block_paths[i])) == 0) {
            return 1;
        }
        
    }
    return 0;
}

void init_path_filter(char **temp) {
    memcpy(block_paths, temp, sizeof(block_paths));
}