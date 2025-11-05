#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks using DFS");
MODULE_AUTHOR("Youssef Hassan, adaptado para kernel 6.16+");

// DFS traversal over task tree
static void dfs(struct task_struct *task) {
    struct task_struct *child; // Pointer to the next child
    struct list_head *list;    // Children list

    // task->comm is the task name
    // task_state_to_char() returns a char describing the task state
    printk(KERN_INFO "Name: %-20s State: %c\tProcess ID: %d\n",
           task->comm, task_state_to_char(task), task->pid);

    list_for_each(list, &task->children) { // Loop over children
        child = list_entry(list, struct task_struct, sibling);
        dfs(child); // Recursive DFS
    }
}

/* Called when the module is loaded */
static int __init entryPoint(void) {
    printk(KERN_INFO "Inserting ListTasksDFS module\n");
    printk(KERN_INFO "Started listing tasks\n");

    dfs(&init_task); // Start DFS from init_task

    printk(KERN_INFO "Stopped listing tasks\n");
    return 0;
}

/* Called when the module is removed */
static void __exit exitPoint(void) {
    printk(KERN_INFO "Removing ListTasksDFS module\n");
}

module_init(entryPoint);
module_exit(exitPoint);
