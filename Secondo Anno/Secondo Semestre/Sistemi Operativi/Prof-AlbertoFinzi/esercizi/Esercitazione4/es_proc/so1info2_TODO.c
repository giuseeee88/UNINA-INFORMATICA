#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

/*
 * TODO 0
 *
 * includere l'header corretto per:
 *
 * current->pid
 * current->comm
 */
#include <linux/sched.h>


#define PROC_NAME "so1info"
#define BUFFER_SIZE 128

static struct proc_dir_entry *proc_entry;

/*
 * Funzione chiamata da:
 *
 * cat /proc/so1info
 */
static ssize_t so1_read(struct file *file,
                        char __user *buffer,
                        size_t length,
                        loff_t *offset)
{
    char message[BUFFER_SIZE];
    int msg_len;

    /*
     * TODO 1
     *
     * Completare sprintf()
     * aggiungendo:
     *
     * - PID corrente
     * - nome del processo
     *
     * Hint:
     *
     * current->pid
     * current->comm
     */
    msg_len = sprintf(message,
                      "SO1 kernel module\nPID: %d\nComm: %s\n",
                      current->pid, current->comm);

    /*
     * EOF dopo prima lettura
     */
    if (*offset > 0)
        return 0;

    /*
     * Copia kernel -> userspace
     */
    if (copy_to_user(buffer,
                     message,
                     msg_len))
        return -EFAULT;

    *offset = msg_len;

    return msg_len;
}

/*
 * Callback supportate
 */
static const struct proc_ops proc_fops = {
    .proc_read = so1_read,
};

/*
 * Init modulo
 */
static int __init so1_init(void)
{
    proc_entry =
        proc_create(PROC_NAME,
                    0,
                    NULL,
                    &proc_fops);

    if (!proc_entry) {

        printk(KERN_ALERT
               "Errore creazione /proc/%s\n",
               PROC_NAME);

        return -ENOMEM;
    }

    printk(KERN_INFO
           "/proc/%s creato\n",
           PROC_NAME);

    return 0;
}

/*
 * Exit modulo
 */
static void __exit so1_exit(void)
{
    remove_proc_entry(PROC_NAME,
                      NULL);

    printk(KERN_INFO
           "/proc/%s rimosso\n",
           PROC_NAME);
}

module_init(so1_init);
module_exit(so1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SO1");
MODULE_DESCRIPTION("SO1 proc module TODO");