#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct timer_list my_timer;

static int period = 2;
static int tick_count = 0;

/*
 * TODO 1
 *
 * aggiungere parametro:
 *
 * max_ticks
 *
 * default = 0
 *
 * Significato:
 *
 * 0 → infinito
 * >0 → numero massimo di tick
 */
static int max_ticks = 0;


/*
 * Parametri modulo
 */
module_param(period, int, 0);

/*
 * TODO 2
 *
 * registrare max_ticks
 * con module_param()
 */
module_param(max_ticks, int, 0);


MODULE_PARM_DESC(period,
                 "Periodo del timer in secondi");

/*
 * TODO 3
 *
 * aggiungere descrizione
 * del parametro max_ticks
 */
MODULE_PARM_DESC(max_ticks,
                 "Numero massimo di tick (0 per infinito)");


static void timer_callback(struct timer_list *t)
{
    tick_count++;

    printk(KERN_INFO
           "hello_timer: tick %d, jiffies=%lu\n",
           tick_count,
           jiffies);

    /*
     * TODO 4
     *
     * Se:
     *
     * max_ticks > 0
     * e tick_count >= max_ticks
     *
     * NON riprogrammare il timer
     *
     * Hint:
     *
     * return;
     */
    if (max_ticks > 0 && tick_count >= max_ticks) {
        return;
    }


    mod_timer(&my_timer,
              jiffies + period * HZ);
}

static int __init hello_timer_init(void)
{
    printk(KERN_INFO
           "hello_timer caricato. "
           "period=%d secondi\n",
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
    timer_delete_sync(&my_timer);

    printk(KERN_INFO
           "hello_timer rimosso\n");
}

module_init(hello_timer_init);
module_exit(hello_timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION(
    "Simple kernel timer TODO");