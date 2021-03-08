#include <darwin_hdrs.h>

extern int (*getdirentries_common_orig)(int fd, void *bufp, size_t bufsize, ssize_t *bytesread,
		                     off_t *offset, int *eofflag, int flags);

extern int getdirentries_common(int fd, void *bufp, size_t bufsize, ssize_t *bytesread,
		                     off_t *offset, int *eofflag, int flags);
