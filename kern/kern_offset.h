#pragma once

#include <darwin_hdrs.h>

extern uint64_t kernel_slide;

extern void (*_bzero)(void *p, size_t n);
extern int (*copyin)(const void *user_addr, void *kernel_addr, size_t nbytes);
extern int (*copyinstr)(const void *uaddr, void *kaddr, size_t len, size_t *done);
extern void *(*current_proc)(void);
extern void (*kprintf)(const char *, ...);
extern void (*proc_name)(int pid, char *buf, int size);
extern pid_t (*proc_pid)(void *);
extern int (*_strcmp)(const char *s1, const char *s2);
extern int (*_strncmp)(const char *s1, const char *s2, int n);
extern int (*_strlen)(const char *s1);
extern int (*_memcpy)(void *, const void *, int n);
extern void *(*unified_kalloc)(size_t sz);
extern void (*unified_kfree)(void *ptr);
extern int (*fp_getfvp)(void *p, int fd, void **resultfp, void **resultvp);
extern int (*vnode_getwithref)(void *vp);
extern int (*vnode_put)(void *vp);
extern int (*fp_drop)(void *p, int fd, void *fp, int);
extern void *(*vfs_context_current)();
extern int (*build_path_with_parent)(void *first_vp, void *parent_vp, char *buff, int buflen, int *outlen, size_t *mntpt_outlen, int flags, void*ctx);
extern int (*copyout)(const void *kernel_addr, void *user_addr, size_t nbytes);


// find these in inlined vfs_context_proc()
struct offsets {
    int OFFSET_THREAD_T_TASK;
    int OFFSET_TASK_BSDINFO;
    int OFFSET_PROC_P_FD;
    int OFFSET_PROC_P_LFLAG;
};
extern struct offsets OOO;

extern void *open1_hook_addr;
extern void *stat_hook_addr;
extern void *getdirentries_hook_addr;

extern int init_kernel_offset(void);