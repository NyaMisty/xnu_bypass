#include <darwin_hdrs.h>

struct stat_args {
	char *path;
	void *ub;
};

extern int (*stat_orig)(void *p, struct stat_args *uap, int32_t *retval);

extern int stat_(void *p, struct stat_args *uap, int32_t *retval);