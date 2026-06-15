// hello_driver.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "hello_driver"

static int major;
static char message[] = "Hello from kernel driver!\n";

/*
 * Funzione chiamata quando userspace esegue read()
 */
static ssize_t hello_read(struct file *file,
                          char __user *buffer,
                          size_t length,
                          loff_t *offset)
{
    int msg_len = sizeof(message);

    // EOF dopo la prima lettura
    if (*offset >= msg_len)
        return 0;

    // Copia dati kernel -> userspace
    if (copy_to_user(buffer, message, msg_len))
        return -EFAULT;

    *offset += msg_len;

    return msg_len;
}

/*
 * Operazioni supportate dal device
 */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read  = hello_read,
};

/*
 * Caricamento modulo
 */
static int __init hello_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0) {
        printk(KERN_ALERT "Errore registrazione driver\n");
        return major;
    }

    printk(KERN_INFO
           "hello_driver caricato. Major = %d\n",
           major);

    return 0;
}

/*
 * Rimozione modulo
 */
static void __exit hello_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);

    printk(KERN_INFO "hello_driver rimosso\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION("Simple hello character driver");