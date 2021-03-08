#include <kern/kern_func.h>

void *vnode_getfromfd(int fd) {
    int error = 0;
    void *vp, *fp;
    vp = fp = NULL;
    void *p = current_proc();
    error = fp_getfvp(p, fd, &fp, &vp);
    if (error) { xprintf("fp_getfvp error %d\n", error); return NULL; }
    error = vnode_getwithref(vp);
    if (error)  goto fail;
fail:
    fp_drop(p, fd, fp, 0);
    if (error) { xprintf("getfromfd error: %d\n", error); return NULL; }
    return vp;
}

void *vnode_getfromfd_ctx(int fd, void *ctx) {
    int error = 0;
    void *vp, *fp;
    vp = fp = NULL;
    void *p = vfs_context_proc(ctx);
    error = fp_getfvp(p, fd, &fp, &vp);
    if (error) { xprintf("fp_getfvp error %d\n", error); return NULL; }
    error = vnode_getwithref(vp);
    if (error)  goto fail;
fail:
    fp_drop(p, fd, fp, 0);
    if (error) { xprintf("getfromfd error: %d\n", error); return NULL; }
    return vp;
}