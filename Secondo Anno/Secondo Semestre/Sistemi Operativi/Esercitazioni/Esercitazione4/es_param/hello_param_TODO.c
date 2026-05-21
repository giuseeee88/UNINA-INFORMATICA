#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>

static char *msg = "hello";
static int repeat = 1;

/*
 * TODO 1
 *
 * aggiungere un parametro:
 *
 * uppercase
 *
 * tipo int
 *
 * default = 0
 */
static int uppercase = 0;


/*
 * Parametri modulo
 */
module_param(msg, charp, 0);
module_param(repeat, int, 0);

/*
 * TODO 2
 *
 * registrare il parametro
 * uppercase
 */
module_param(uppercase, int, 0);


MODULE_PARM_DESC(msg,
                 "Messaggio da stampare");

MODULE_PARM_DESC(repeat,
                 "Numero ripetizioni");

/*
 * TODO 3
 *
 * aggiungere descrizione
 * del parametro uppercase
 */
MODULE_PARM_DESC(uppercase,
                 "Se 1, stampa in maiuscolo");


/*
 * Init modulo
 */
static int __init hello_init(void)
{
    int i;

    printk(KERN_INFO
           "hello_param loaded\n");

    /*
     * TODO 4
     *
     * se uppercase == 1
     * convertire msg in maiuscolo
     *
     * Hint:
     *
     * toupper()
     *
     * ciclo sui caratteri
     */
    if (uppercase == 1) {
        char *p = msg;
        while (*p) {
            *p = toupper(*p);
            p++;
        }
    }

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
    "Module parameters TODO");