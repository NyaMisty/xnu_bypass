#include <kern/kern_func.h>
#include <kern/kern_hook.h>
#include <hooks/hooks.h>

int main(int argc, char **argv){
    int ret;
    if ((ret = init_xnuspy())) {
        printf("init_xnuspy failed\n");
        return 1;
    }
    printf("init_xnuspy success\n");
    
    if((ret = init_kern_func())){
        printf("init_kern_func failed: %s\n", strerror(errno));
        return 1;
    }
    printf("init_kern_func success\n");

    if((ret = install_all_hooks())){
        printf("install_all_hooks failed\n");
        return 1;
    }
    printf("install_all_hooks success\n");

    for(;;){
        sleep(1);
    }

    return 0;
}
