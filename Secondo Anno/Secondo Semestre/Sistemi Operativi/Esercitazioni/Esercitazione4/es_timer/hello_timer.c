#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct timer_list my_timer;

static int period = 2;
static int tick_count = 0;

module_param(period, int, 0);
MODULE_PARM_DESC(period, "Periodo del timer in secondi");

static void timer_callback(struct timer_list *t)
{
    tick_count++;

    printk(KERN_INFO
           "hello_timer: tick %d\n",
           tick_count);

    mod_timer(&my_timer,
              jiffies + period * HZ);
}

static int __init hello_timer_init(void)
{
    printk(KERN_INFO
           "hello_timer caricato. period=%d secondi\n",
           period);

    timer_setup(&my_timer,
                timer_callback,
                0);

    mod_timer(&my_timer,
              jiffies + period * HZ);

    return 0;
}

static void __exit hello_timer_exit(void)
{
    timer_delete_sync();

    printk(KERN_INFO
           "hello_timer rimosso\n");
}

module_init(hello_timer_init);
module_exit(hello_timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION("Simple kernel timer module");