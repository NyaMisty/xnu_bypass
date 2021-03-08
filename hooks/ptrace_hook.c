#include <kern/kern_func.h>
#include <utils/helpers.h>
#include <filter/filters.h>
#include "ptrace_hook.h"
//#include <sys/ptrace.h>

int (*ptrace_orig)(void *p, struct ptrace_args *uap, int32_t *retval);

#define PT_DENY_ATTACH 31
#define PT_TRACEME 0

int ptrace_(void *p, struct ptrace_args *uap, int32_t *retval) {
    /*if (uap->req == PT_DENY_ATTACH) {
        return 0;
    }
    return ptrace_orig(p, uap, retval);*/

    char *caller_name = NULL;

    caller_name = log_get_caller("ptrace", "[unk]", 1);
    if(!caller_name)
        goto orig;

    if(check_caller(caller_name)){
        xprintf("denying ptrace(%p, %d, %p, %p)\n", uap->req, uap->pid, uap->addr, uap->data);
        //if (uap->req == PT_DENY_ATTACH || uap->req == PT_TRACEME) {
            return 0;
        //}
    }

orig:
    if(caller_name)
        unified_kfree(caller_name);

    return ptrace_orig(p, uap, retval);
}