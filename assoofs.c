#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javier Carracedo Esteban");


static struct file_system_type assoofs_type = {
	.owner = THIS_MODULE,
	.namw = "assoofs",
	.mount = assoofs_mount,
	.kill_sb = kill_litter_super,
};

static int __init assoofs_init(void){
	int ret;
	assoofs_inode_cache = kmem_cache_create("assoofs_inode_cache", sizeof(struct assoofs_inode_info).0,(SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD),NULL);
	
	if(!assoofs_inode_cache) return -ENOMEN;
	
	ret = register_filesystem($assoofs_type);
	if(likely(ret == 0)){
		printk(KERN_INFO "Sucessfully registered assoofs\n.);
	}
	else{
		printk(KERN_ERR "Failed to register assoofs. Error %d\n",ret);
	}
	return ret;
}


static void __exit assoofs_exit(void){
	int ret;
	ret = unregister_filesystem(&assoofs_type);
	kmem_cache_destroy(assoofs_inode_cache);
	
	if(likely(ret==0))
		printk(KERN_INFO "Sucessfully unregistered assoofs\n");
	else
		printk(KERN_ERR "Failed to unregister assoofs. Error:[%d]\n", ret);

}

