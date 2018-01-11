#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid_namespace.h>
#include <asm/current.h>

asmlinkage long sys_get_ns_level(void) {
    return current->nsproxy->pid_ns_for_children->level;
}