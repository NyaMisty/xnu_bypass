#include <kern/kern_hook.h>
#include <kern/kern_offset.h>
#include "hooks.h"

int install_all_hooks() {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types"

    int ret = 0;
    if(( ret = install_hook(open1_hook_addr, open1, &open1_orig) )){
        printf("Could not hook open1: %s\n", strerror(errno));
        return 1;
    }
    if(( ret = install_hook(stat_hook_addr, stat_, &stat_orig) )){
        printf("Could not hook stat: %s\n", strerror(errno));
        return 1;
    }
    if(( ret = install_hook(getdirentries_hook_addr, getdirentries_common, &getdirentries_common_orig) )){
        printf("Could not hook getdirent: %s\n", strerror(errno));
        return 1;
    }
    return 0;

#pragma clang diagnostic pop

}