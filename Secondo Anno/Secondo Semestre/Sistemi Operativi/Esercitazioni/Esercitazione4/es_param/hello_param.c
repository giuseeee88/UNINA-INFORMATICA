#include <linux/module.h>
#include <linux/kernel.h>

static char *msg = "hello";
static int repeat = 1;

/*
 * Parametri modulo
 */
module_param(msg, charp, 0);
module_param(repeat, int, 0);

MODULE_PARM_DESC(msg,
                 "Messaggio da stampare");

MODULE_PARM_DESC(repeat,
                 "Numero ripetizioni");

/*
 * Init modulo
 */
static int __init hello_init(void)
{
    int i;

    printk(KERN_INFO
           "hello_param loaded\n");

    for (i = 0; i < repeat; i++) {

        printk(KERN_INFO
               "%s\n",
               msg);
    }

    return 0;
}

/*
 * Exit modulo
 */
static void __exit hello_exit(void)
{
    printk(KERN_INFO
           "hello_param removed\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION(
    "Simple module parameters example");