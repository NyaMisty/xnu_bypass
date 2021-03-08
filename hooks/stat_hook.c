#include <kern/kern_func.h>
#include <utils/helpers.h>
#include <filter/filters.h>
#include "stat_hook.h"

/* bsd/sys/namei.h */
#define PATHBUFLEN 256

int (*stat_orig)(void *p, struct stat_args *uap, int32_t *retval);

int stat_(void *p, struct stat_args *uap, int32_t *retval) {
    char *path = NULL, *caller_name = NULL;

    if(!(path = try_read_str(uap->path, PATHBUFLEN)))
        goto orig;

    caller_name = log_get_caller("stat", path, 0);
    if(!caller_name)
        goto orig;

    if(check_caller(caller_name) && check_path(path)){
        xprintf("denying stat for '%s'\n", path);
        unified_kfree(path);
        *retval = -1;
        return ENOENT;
    }

orig:
    if(path)
        unified_kfree(path);
    if(caller_name)
        unified_kfree(caller_name);

    return stat_orig(p, uap, retval);
}