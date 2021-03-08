#include <darwin_hdrs.h>
#include "kern_offset.h"

#define xprintf(f_, ...) kprintf(("xnuspy: %s: " f_), __func__, __VA_ARGS__)

extern uint8_t curcpu(void);
extern pid_t caller_pid(void);

extern int init_kern_func();

void *vfs_context_proc(void *ctx);