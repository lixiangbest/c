/*************************************************************************
	> File Name: kernel.c
	> Description: netlink kernel
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月26日 星期四 17时08分52秒
 ************************************************************************/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/sched.h>
#include<net/sock.h>
#include<linux/netlink.h>

#define NL_MYTEST 17
static struct sock *nlfd = NULL;
void nl_data_recv(struct sk_buff *__skb){
	struct sk_buff *skb;
	struct nlmsghdr *nlhdr;
	u32 pid;
	int ret;
	int len = NLMSG_SPACE(1024);
	char str[100];
	printk("KNL: Get data from sk_buff.\n");
	skb = skb_get(__skb);

	if(skb->len >= NLMSG_SPACE(0)){
		nlhdr = nlmsg_hdr(skb);
		printk("KNL: Recv %s.\n", (char *)NLMSG_DATA(nlhdr));
		memcpy(str, NLMSG_DATA(nlhdr, sizeof(str)));
		pid = nlhdr->nlmsg_pid;/*send process pid*/
		printk("KNL: Pid is %d\n", pid);
		kfree_skb(skb);
		skb = alloc_skb(len, GFP_ATOMIC);//allocate buffer
		if(!skb){
			printk("KNL: Allocate failed.\n");
			return;
		}
		/*send data*/
		nlhdr = nlmsg_put(skb, 0, 0, 0, 1024, 0);//init netlink header
		NETLINK_CB(skb).pid = 0;//from kernel
		memcpy(NLMSG_DATA(nlhdr), str, sizeof(str));
		printk("KNL: Going to send.\n");
		if( ret = netlink_unicast(nlfd, skb, pid, MSG_DONTWAIT) ){
			printk("KNL: Cannot unicast skb(%d)\n", ret);
		}
		printk("KNL: Send is OK.\n");
	}
	return;
}

static int __init init(void){
	if( nlfd = netlink_kernel_create(&init_net, NL_MYTEST, 0, nl_data_recv, NULL, THIS_MODULE) ){
		printk("KNL: Can not create a netlink socket.\n");
		return -1;
	}
	printk("KNL: Create netlink socket ok.\n");
	return 0;
}

static void __exit fini(void){
	if(nlfd != NULL){
		sock_release(nlfd->sk_socket);
	}
	printk("KNL: Remove ok.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Taylor");
MODULE_VERSION("2.6.32");

module_init(init);
module_exit(fini);
