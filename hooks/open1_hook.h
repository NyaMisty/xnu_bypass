#include <darwin_hdrs.h>

/* bsd/sys/uio.h */
enum uio_seg {
    UIO_USERSPACE       = 0,    /* kernel address is virtual,  to/from user virtual */
    UIO_SYSSPACE        = 2,    /* kernel address is virtual,  to/from system virtual */
    UIO_USERSPACE32     = 5,    /* kernel address is virtual,  to/from user 32-bit virtual */
    UIO_USERSPACE64     = 8,    /* kernel address is virtual,  to/from user 64-bit virtual */
    UIO_SYSSPACE32      = 11    /* deprecated */
};

#define UIO_SEG_IS_USER_SPACE( a_uio_seg )  \
    ( (a_uio_seg) == UIO_USERSPACE64 || (a_uio_seg) == UIO_USERSPACE32 || \
      (a_uio_seg) == UIO_USERSPACE )

/* bsd/sys/namei.h */
#define PATHBUFLEN 256

struct nameidata {
    char * /* __user */ ni_dirp;
    enum uio_seg ni_segflag;
    /* ... */
};

extern int (*open1_orig)(void *vfsctx, struct nameidata *ndp, int uflags,
        void *vap, void *fp_zalloc, void *cra, int32_t *retval);

extern int open1(void *vfsctx, struct nameidata *ndp, int uflags,
        void *vap, void *fp_zalloc, void *cra, int32_t *retval);
