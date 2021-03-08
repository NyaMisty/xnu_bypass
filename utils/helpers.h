#include <kern/kern_func.h>

extern char *log_get_caller(const char *fn, const char *param, int dolog);
extern void *try_read_str(void *addr, size_t maxLen);