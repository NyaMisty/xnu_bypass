#include <kern/kern_func.h>
#include <utils/helpers.h>
#include <filter/filters.h>
#include "open1_hook.h"


int (*open1_orig)(void *vfsctx, struct nameidata *ndp, int uflags,
        void *vap, void *fp_zalloc, void *cra, int32_t *retval);

int open1(void *vfsctx, struct nameidata *ndp, int uflags,
        void *vap, void *fp_zalloc, void *cra, int32_t *retval){
    char *path = NULL, *caller_name = NULL;

    if(!(ndp->ni_dirp && UIO_SEG_IS_USER_SPACE(ndp->ni_segflag)))
        goto orig;

    if(!(path = try_read_str(ndp->ni_dirp, PATHBUFLEN)))
        goto orig;

    caller_name = log_get_caller("open1", path, 0);

    if(!caller_name)
        goto orig;
    if(check_caller(caller_name)){
        //xprintf("%s opening %s with flag %x\n", caller_name, path, uflags);
        if (check_path(path)){
                xprintf("denying open for '%s'\n", path);
                unified_kfree(path);
                unified_kfree(caller_name);
                *retval = -1;
                return ENOENT;
        }
    }

orig:
    if(caller_name)
        unified_kfree(caller_name);
    if(path)
        unified_kfree(path);

    return open1_orig(vfsctx, ndp, uflags, vap, fp_zalloc, cra, retval);
}