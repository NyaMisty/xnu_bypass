#include "kern_func.h"
#include "kern.h"
#include "kern_hook.h"
#include "xnuspy_ctl.h"

long SYS_xnuspy_ctl = 0;

int init_xnuspy() {
    size_t oldlen = sizeof(long);
    int ret = sysctlbyname("kern.xnuspy_ctl_callnum", &SYS_xnuspy_ctl,
            &oldlen, NULL, 0);

    if(ret == -1){
        printf("sysctlbyname with kern.xnuspy_ctl_callnum failed: %s\n",
                strerror(errno));
        return 1;
    }

    ret = syscall(SYS_xnuspy_ctl, XNUSPY_CHECK_IF_PATCHED, 0, 0, 0);

    if(ret != 999){
        printf("xnuspy_ctl isn't present?\n");
        return 1;
    }

    return 0;
}

int install_hook(void *target, void *replace, void **orig) {
    return syscall(SYS_xnuspy_ctl, XNUSPY_INSTALL_HOOK, target, replace, orig);
}