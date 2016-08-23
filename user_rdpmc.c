/*
 * This code is dual licensed under the MIT and GPLv2 licenses.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <linux/cpumask.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SOftware Development Team");
MODULE_DESCRIPTION("Enable RDPMC from ring 3 (userland)");
MODULE_VERSION("0.1");

static void set_pce(void *arg);
static int __init user_rdpmc_init(void);
static void __exit user_rdpmc_exit(void);

static int num_cpus = -1; // set for real upon attach

static void
set_pce(void *arg)
{
    int to_val = (arg != 0);
    u_int32_t cr4_val;

    cr4_val = read_cr4();
    if (to_val) {
        cr4_val |= X86_CR4_PCE;
    } else {
        cr4_val &= ~X86_CR4_PCE;
    }

    write_cr4(cr4_val);
}

static int __init
user_rdpmc_init(void){
    int cpu;

    num_cpus = num_online_cpus();

    printk(KERN_INFO "Enabling RDPMC from ring 3 for %d CPUs\n", num_cpus);
    for (cpu = 0; cpu < num_cpus; cpu++) {
        smp_call_function_single(cpu, set_pce, (void *) 1, 1);
    }

   return 0;
}

static void __exit
user_rdpmc_exit(void)
{
    int cpu;

    printk(KERN_INFO "Disabling RDPMC from ring 3 for %d CPUs\n", num_cpus);
    for (cpu = 0; cpu < num_cpus; cpu++) {
        smp_call_function_single(cpu, set_pce, (void *) 0, 1);
    }
}

module_init(user_rdpmc_init);
module_exit(user_rdpmc_exit);
