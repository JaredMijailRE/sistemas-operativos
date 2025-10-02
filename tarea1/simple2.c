#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>     // Para GOLDEN_RATIO_PRIME
#include <linux/jiffies.h>  // Para jiffies
#include <asm/param.h>      // Para HZ
#include <linux/gcd.h>      // Para gcd()

static unsigned long start_jiffies;

static int __init simple_init(void)
{
    start_jiffies = jiffies;   // Guardamos jiffies al inicio

    printk(KERN_INFO "Loading Kernel Module\n");

    // GOLDEN_RATIO_PRIME
    printk(KERN_INFO "GOLDEN_RATIO_PRIME = %lu\n", GOLDEN_RATIO_PRIME);

    // jiffies y HZ
    printk(KERN_INFO "jiffies at load: %lu\n", jiffies);
    printk(KERN_INFO "HZ (timer frequency) = %d\n", HZ);

    return 0;
}

static void __exit simple_exit(void)
{
    unsigned long end_jiffies = jiffies;
    unsigned long elapsed_jiffies = end_jiffies - start_jiffies;
    unsigned long elapsed_seconds = elapsed_jiffies / HZ;

    printk(KERN_INFO "Removing Kernel Module\n");

    // gcd
    printk(KERN_INFO "gcd(3300, 24) = %lu\n", gcd(3300, 24));

    // jiffies al descargar
    printk(KERN_INFO "jiffies at unload: %lu\n", end_jiffies);

    // Tiempo transcurrido
    printk(KERN_INFO "Time elapsed (in jiffies): %lu\n", elapsed_jiffies);
    printk(KERN_INFO "Time elapsed (in seconds): %lu\n", elapsed_seconds);
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Extended Simple Module with GOLDEN_RATIO_PRIME, jiffies, gcd and HZ");
MODULE_AUTHOR("TuNombre");
