#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define DEVICE_NAME "hello_driver"
#define BUFFER_SIZE 128

static int major;

/*
 * Buffer del driver:
 * inizialmente contiene il messaggio di default
 */
static char message[BUFFER_SIZE] =
    "Hello from kernel driver!\n";

/*
 * READ
 * già funzionante
 */
static ssize_t hello_read(struct file *file,
                          char __user *buffer,
                          size_t length,
                          loff_t *offset)
{
    size_t msg_len = strlen(message);
    size_t bytes_to_copy;

    // EOF
    if (*offset >= msg_len)
        return 0;

    bytes_to_copy =
        min(length, msg_len - (size_t)*offset);

    if (copy_to_user(buffer,
                     message + *offset,
                     bytes_to_copy))
        return -EFAULT;

    *offset += bytes_to_copy;

    return bytes_to_copy;
}

/*
 * WRITE
 *
 * TODO:
 * Implementare questa funzione.
 *
 * Obiettivo:
 *
 * echo "ciao" > /dev/hello_driver
 *
 * deve fare in modo che:
 *
 * cat /dev/hello_driver
 *
 * restituisca:
 *
 * ciao
 */
static ssize_t hello_write(struct file *file,
                           const char __user *buffer,
                           size_t length,
                           loff_t *offset)
{
    /*
     * TODO 1
     *
     * Evitare overflow del buffer.
     *
     * Se length >= BUFFER_SIZE,
     * limitare la lunghezza.
     */
    size_t bytes_to_copy = min(length, (size_t)(BUFFER_SIZE - 1));

    /*
     * TODO 2
     *
     * Copiare dati da userspace
     * al buffer kernel:
     *
     * usare copy_from_user()
     */
    if (copy_from_user(message, buffer, bytes_to_copy))
        return -EFAULT;

    /*
     * TODO 3
     *
     * Terminare la stringa con '\0'
     */
    message[bytes_to_copy] = '\0';

    /*
     * TODO 4
     *
     * Restituire numero byte scritti
     */

    return bytes_to_copy;
}

/*
 * Operazioni supportate dal device
 */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read  = hello_read,

    /*
     * TODO 5
     *
     * aggiungere supporto write
     */
    .write = hello_write,
};

/*
 * Init modulo
 */
static int __init hello_init(void)
{
    major =
        register_chrdev(0,
                         DEVICE_NAME,
                         &fops);

    if (major < 0) {
        printk(KERN_ALERT
               "Errore registrazione driver\n");
        return major;
    }

    printk(KERN_INFO
           "hello_driver caricato. Major = %d\n",
           major);

    return 0;
}

/*
 * Exit modulo
 */
static void __exit hello_exit(void)
{
    unregister_chrdev(major,
                       DEVICE_NAME);

    printk(KERN_INFO
           "hello_driver rimosso\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION(
    "Dummy driver with read/write TODO");