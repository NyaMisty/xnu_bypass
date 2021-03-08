#include "kern_offset.h"
#include "kern.h"
#include "xnuspy_ctl.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-conversion"

void (*_bzero)(void *p, size_t n);
int (*copyin)(const void *user_addr, void *kernel_addr, size_t nbytes);
int (*copyinstr)(const void *uaddr, void *kaddr, size_t len, size_t *done);
int (*copyout)(const void *kernel_addr, void *user_addr, size_t nbytes) = 0xFFFFFFF007D02BF4;
void *(*current_proc)(void);
void (*kprintf)(const char *, ...);
void (*proc_name)(int pid, char *buf, int size);
pid_t (*proc_pid)(void *);
int (*_strcmp)(const char *s1, const char *s2);
int (*_strncmp)(const char *s1, const char *s2, int n);
int (*_strlen)(const char *s1);
int (*_memcpy)(void *, const void *, int n);
void *(*unified_kalloc)(size_t sz);
void (*unified_kfree)(void *ptr);
int (*fp_getfvp)(void *p, int fd, void **resultfp, void **resultvp) = 0xFFFFFFF007FCEE24;
int (*vnode_getwithref)(void *vp) = 0xFFFFFFF007D8BF88;
int (*vnode_put)(void *vp) = 0xFFFFFFF007D89A90;
int (*fp_drop)(void *p, int fd, void *fp, int) = 0xFFFFFFF007FC93F4;
void *(*vfs_context_current)() = 0xFFFFFFF007DAFBEC;
int (*build_path_with_parent)(void *first_vp, void *parent_vp, char *buff, int buflen, int *outlen, size_t *mntpt_outlen, int flags, void*ctx) = 0xFFFFFFF007D77C90;

uint64_t kernel_slide;

//struct offsets OOO = { -1, -1, -1, -1 };
struct offsets OOO = { 0 };

// must be UNSLID!
void *open1_hook_addr = 0xFFFFFFF007D99268;
void *stat_hook_addr = 0xFFFFFFF007D9E374;
void *getdirentries_hook_addr = 0xFFFFFFF007DA3450;
void *ptrace_hook_addr = 0xFFFFFFF00801A7A4;

#pragma clang diagnostic pop

int init_kernel_offset(void){
    int ret;
#define GET(a, b) \
    do { \
        ret = syscall(SYS_xnuspy_ctl, XNUSPY_CACHE_READ, a, b, 0); \
        if(ret){ \
            printf("%s: failed getting %s\n", __func__, #a); \
            return ret; \
        } \
    } while (0)

    GET(BZERO, &_bzero);
    GET(COPYIN, &copyin);
    GET(COPYOUT, &copyout);
    GET(COPYINSTR, &copyinstr);
    GET(CURRENT_PROC, &current_proc);
    GET(KPRINTF, &kprintf);
    GET(PROC_NAME, &proc_name);
    GET(PROC_PID, &proc_pid);
    GET(STRCMP, &_strcmp);
    GET(STRNCMP, &_strncmp);
    GET(UNIFIED_KALLOC, &unified_kalloc);
    GET(UNIFIED_KFREE, &unified_kfree);
    GET(STRLEN, &_strlen);
    GET(MEMMOVE, &_memcpy);
    GET(KERNEL_SLIDE, &kernel_slide);

    /*void *tempcopyout = NULL;
    GET(COPYOUT, &tempcopyout);
    printf("xnuspy copyout: %p, real copyout: %p", tempcopyout - kernel_slide, copyout); //unslid*/

#define SLIDE(a) \
    do {\
	a += kernel_slide;\
    } while(0)

    //SLIDE(copyout);
    SLIDE(fp_getfvp);
    SLIDE(vnode_getwithref);
    SLIDE(vnode_put);
    SLIDE(fp_drop);
    SLIDE(vfs_context_current);
    SLIDE(build_path_with_parent);

    OOO.OFFSET_THREAD_T_TASK =  792;
    OOO.OFFSET_TASK_BSDINFO =  896;
    OOO.OFFSET_PROC_P_FD = 264;
    OOO.OFFSET_PROC_P_LFLAG = 329;

    return 0;
}