#include "helpers.h"

char *log_get_caller(const char *fn, const char *param, int dolog) {
    uint8_t cpu = curcpu();
    pid_t caller = caller_pid();

    char *caller_name = unified_kalloc(MAXCOMLEN + 1);

    if(!caller_name)
        return NULL;

    /* proc_name doesn't bzero for some version of iOS 13 */
    _bzero(caller_name, MAXCOMLEN + 1);
    proc_name(caller, caller_name, MAXCOMLEN + 1);
    if (dolog)
        xprintf("%s: (CPU %d): '%s' (%d) wants to call '%s' on '%s'\n", fn, cpu,
                caller_name, caller, fn, param);
    return caller_name;
}

void *try_read_str(void *addr, size_t maxLen) {
    char *path = NULL;

    size_t sz = maxLen;

    if(!(path = unified_kalloc(sz)))
        return NULL;

    _bzero(path, sz);

    size_t pathlen = 0;
    int res = copyinstr(addr, path, sz, &pathlen);

    if(res)
        return NULL;

    path[pathlen - 1] = '\0';
    return path;
}
