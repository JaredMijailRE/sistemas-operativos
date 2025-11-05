#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks linearly");
MODULE_AUTHOR("Youssef Hassan, adaptado para kernel 6.16+");

/* This function is called when the module is loaded. */
static int __init entryPoint(void) {
    struct task_struct *task; // Pointer to the task whose info will be printed

    printk(KERN_INFO "Inserting ListTasksLinear module\n");    
    printk(KERN_INFO "Started listing tasks\n");

    // Loop over all tasks
    for_each_process(task) {
        // task->comm  → name of the task
        // task_state_to_char(task) → character representing state
        // task->pid   → process ID
        printk(KERN_INFO "Name: %-20s State: %c\tProcess ID: %d\n",
               task->comm, task_state_to_char(task), task->pid);
    }

    printk(KERN_INFO "Stopped listing tasks\n");
    return 0;
}

/* This function is called when the module is removed. */
static void __exit exitPoint(void) {
    printk(KERN_INFO "Removing ListTasksLinear module\n");
}

/* Register entry and exit points */
module_init(entryPoint);
module_exit(exitPoint);
