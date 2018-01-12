#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/get_pdps_of_pid_at_ancestor_ns.h>
#include <linux/sched.h>
#include <linux/pid_namespace.h>
#include <asm/current.h>

asmlinkage long sys_get_pdps_of_pid_at_ancestor_ns(struct pdps_with_pid_at_ancestor_ns *pdps, long pid) {
    int i, level;
    struct task_struct *task = current;
    struct pid_namespace *ns = task->nsproxy->pid_ns_for_children;
    if (ns == NULL) {
        return -1;
    }
    level = ns->level;
    for (i = level; i >= 0; i--) {
        pdps[i].process_descriptor_pointer = (long) find_task_by_pid_ns(pid, ns);
        ns = ns->parent;
        if (ns == NULL) {
            return -1;
        }
    }
    return level + 1;
}