#include "system/scheduler.h"
#include "system/scheduler/choose_next.h"
#include "system/processQueue.h"
#include "type.h"

struct ProcessQueue scheduler_queue = {.first = NULL, .last = NULL};

struct Process* scheduler_curr = NULL;

void scheduler_add(struct Process* process) {
    process_queue_push(&scheduler_queue, process);
}

void scheduler_do(void) {

    if (scheduler_curr != NULL) {
        __asm__ __volatile ("mov %%ebp, %0":"=r"(scheduler_curr->mm.esp)::);
    }

    choose_next();

    if (scheduler_curr != NULL) {
        __asm__ __volatile__ ("mov %0, %%ebp"::"r"(scheduler_curr->mm.esp));
    }
}

void scheduler_remove(struct Process* process) {
    if (scheduler_curr != NULL && process->pid == scheduler_curr->pid) {
        scheduler_curr = NULL;
    }
    process_queue_remove(&scheduler_queue, process);
}


struct Process* scheduler_current(void) {
    if (scheduler_curr == NULL) {
        return NULL;
    }

    return scheduler_curr;
}

