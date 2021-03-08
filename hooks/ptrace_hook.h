#include <darwin_hdrs.h>

struct ptrace_args {
	uint64_t req;
	pid_t pid;
	void *addr;
	uint8_t data;
};

extern int (*ptrace_orig)(void *p, struct ptrace_args *uap, int32_t *retval);

extern int ptrace_(void *p, struct ptrace_args *uap, int32_t *retval);