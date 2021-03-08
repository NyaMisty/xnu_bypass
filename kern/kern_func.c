#include "xnuspy_ctl.h"
#include "kern.h"
#include "kern_func.h"

int init_kern_func(void){
    return init_kernel_offset();
}

uint8_t curcpu(void){
    uint64_t mpidr_el1;
    asm volatile("mrs %0, mpidr_el1" : "=r" (mpidr_el1));
    return (uint8_t)(mpidr_el1 & 0xff);
}

pid_t caller_pid(void){
    return proc_pid(current_proc());
}

void *vfs_context_proc(void *ctx) {
    if (ctx && *(uint64_t *)ctx) { //ctx && ctx->vc_thread
        uint64_t proc = 0;
        uint64_t v17 = *(uint64_t *)(*(uint64_t *)ctx + OOO.OFFSET_TASK_BSDINFO); // th->task
        if (v17) { proc = *(uint64_t *)(v17 + OOO.OFFSET_TASK_BSDINFO); } // th->task->bsd_info
        if (proc) {
            if (*(uint64_t *)(proc + OOO.OFFSET_PROC_P_FD) && (*(char *)(proc + OOO.OFFSET_PROC_P_LFLAG) & 1) == 0) { // proc->p_fd && proc->p_lflag & P_LVFORK
                return (void *)proc;
            }
        }
        return current_proc();
    }
    return NULL;
}