/*************************************************************************
	> File Name: myifconfig.c
	> Description: my ifconfig.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月23日 星期一 02时53分46秒
 ************************************************************************/
#include "unpifi.h"

int print_if_addr(int fd, char *i_name);/*print interface ip addr.*/
int print_if_mac(int fd, char *i_name);/*print interface mac addr.*/
int print_if_broadaddr(int fd, char *i_name);/*print interface broadaddr.*/
int print_if_mask(int fd, char *i_name);/*print interface mask*/
int print_if_mtu(int fd, char *i_name);/*print interface mtu*/
int print_all_interface();/*print all interfaces info*/
int print_if_addr6(char *i_name);/*print interface ipv6 addr*/
int print_interface_info(char *i_name);/*print interface info of above all*/
int set_if_up(char *i_name);/*start interface*/
int set_if_down(char *i_name);/*close interface*/
int set_if_ip(char *i_name, char *ip_str);/*set the interface ip addr.*/
void usage();/*print the usage of programe*/

int main(int argc, char **argv){
	printf("\nTaylor:my ifconfig cmd complish use ioctl function\n");

	switch(argc){
		case 1:
			print_all_interface();
			break;
		case 2:
			print_interface_info(argv[1]);
			break;
		case 3:
			if(strcmp(argv[2], "up") == 0)
				set_if_up(argv[1]);
			else if(strcmp(argv[2], "down") == 0)
				set_if_down(argv[2]);
			else
				set_if_ip(argv[1], argv[2]);
			break;
		default:
			usage();
			break;
	}

	return 0;
}

void usage(){
	printf("usage: ./myifconfig [interface(lo,eth0) [down|up|ip]]\n");
}

int print_if_addr(int fd, char *if_name){
	struct sockaddr_in *ip;
	struct arpreq arp_req;
	unsigned char *ptr;
	struct ifreq ifr;
	int sockfd;

	strcpy(ifr.ifr_name, if_name);

	if(ioctl(fd, SIOCGIFADDR, &ifr) < 0){
		err_sys("ioctl SIOCGIFADDR error");
	}

	ip = (struct sockaddr_in *)&ifr.ifr_addr;/*get ipv4 addr*/
	printf("ip: %s\n", inet_ntoa(ip->sin_addr));/*network order to host order*/

	ip = (struct sockaddr_in *)&arp_req.arp_pa;
	memcpy(ip, &ifr.ifr_addr, sizeof(struct sockaddr_in));

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	if(ioctl(sockfd, SIOCGARP, &arp_req) < 0)
		err_ret("ioctl SIOCGARP");

	ptr = &arp_req.arp_ha.sa_data[0];
	printf("arp: %02x:%02x:%02x:%02x:%02x:%02x\n", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
	
	return 0;
}

int print_if_broadaddr(int fd, char *if_name){
	struct sockaddr_in *ip;
	struct ifreq ifr;

	strcpy(ifr.ifr_name, if_name);

	if(ioctl(fd, SIOCGIFBRDADDR, &ifr) < 0){
		err_sys("ioctl SIOCGIFBRDADDR error");
	}

	ip = (struct sockaddr_in *)&ifr.ifr_broadaddr;/*get ipv4 addr*/
	printf("broadcast: %s\n", inet_ntoa(ip->sin_addr));/*network order to host order*/

	return 0;
}

int print_if_mask(int fd, char *if_name){
	struct sockaddr_in *ip;
	struct ifreq ifr;

	strcpy(ifr.ifr_name, if_name);

	if(ioctl(fd, SIOCGIFNETMASK, &ifr) < 0){
		err_sys("ioctl SIOCGIFNETMASK error");
	}

	ip = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_netmask;/*get ipv4 addr*/
	printf("mask: %s\n", inet_ntoa(ip->sin_addr));/*network order to host order*/

	return 0;
}

int print_if_mac(int fd, char *if_name){
	unsigned char *p;/*notice: unsigned char*/
	struct ifreq ifr;

	strcpy(ifr.ifr_name, if_name);

	if(ioctl(fd, SIOCGIFHWADDR, &ifr) < 0){
		err_sys("ioctl SIOCGIFHWADDR error");
	}

	p = (char *)&ifr.ifr_ifru.ifru_hwaddr.sa_data[0];/*get interface mac addr*/
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n", *p, *(p+1), *(p+2), *(p+3), *(p+4), *(p+5));
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n", *p, *p++, *p++, *p++, *p++, *p++);

	return 0;
}

int print_if_mtu(int fd, char *if_name){
	unsigned int mtu;
	struct ifreq ifr;

	strcpy(ifr.ifr_name, if_name);

	if(ioctl(fd, SIOCGIFMTU, &ifr) < 0){
		err_sys("ioctl SIOCGIFMTU error");
	}

	mtu = ifr.ifr_ifru.ifru_mtu;/*get mtu*/
	
	printf("mtu: %d\n", mtu);

	return 0;
}

int print_if_addr6(char *if_name){
	unsigned int mtu;
	struct ifreq ifr;
	int sockfd;

	if( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
		err_sys("socket error");
	}

	return 0;
}

int print_all_interface(){
	struct ifconf ifc;
	struct ifreq *ifr_p;
	int sockfd, len, old_len = 0, i, icount;
	char *buf;

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		err_sys("socket error");
	}

	len = 10 * sizeof(struct ifreq);
	for(;;){
		if( (buf = malloc(len)) == NULL ){
			err_sys("malloc error");
		}
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if(ioctl(sockfd, SIOCGIFCONF, &ifc) < 0){
			err_sys("ioctl SIOCGIFCONF error");
		}
		if(ifc.ifc_len == old_len)
			break;
		old_len = ifc.ifc_len;
		len += 10 * sizeof(struct ifreq);
		free(buf);
	}
	icount = ifc.ifc_len/sizeof(struct ifreq);
	printf("we have %d interface\n", icount);

	for(i = 0; i < icount; i++){
		ifr_p = &ifc.ifc_req[i];
		printf("\ninterface [%s]:\n", ifr_p->ifr_name);

		print_if_addr(sockfd, ifr_p->ifr_name);
		print_if_broadaddr(sockfd, ifr_p->ifr_name);
		print_if_mask(sockfd, ifr_p->ifr_name);
		print_if_mac(sockfd, ifr_p->ifr_name);
		print_if_mtu(sockfd, ifr_p->ifr_name);
	}
	close(sockfd);
	return 0;
}

int print_interface_info(char *if_name){
	int sockfd;
	/*create sockfd for interface test.*/
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		err_sys("socket error");
	}

	printf("%s:\n", if_name);
	print_if_addr(sockfd, if_name);
	print_if_broadaddr(sockfd, if_name);
	print_if_mask(sockfd, if_name);
	print_if_mac(sockfd, if_name);
	print_if_mtu(sockfd, if_name);
	close(sockfd);
	return 0;
}

/*start interface*/
int set_if_up(char *if_name){
	struct ifreq ifr;
	int sockfd;

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		err_sys("socket error");
	}

	strcpy(ifr.ifr_name, if_name);
	if(ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0){
		err_sys("ioctl SIOCGIFFLAGS error");
	}
	ifr.ifr_flags |= IFF_UP;
	if(ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0){
		err_sys("ioctl SIOCSIFFLAGS error");
	}
	return 0;
}

/*shutdown interface*/
int set_if_down(char *if_name){
	struct ifreq ifr;
	int sockfd;

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		err_sys("socket error");
	}

	strcpy(ifr.ifr_name, if_name);
	if(ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0){
		err_sys("ioctl SIOCGIFFLAGS error");
	}
	ifr.ifr_flags &= ~IFF_UP;
	if(ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0){
		err_sys("ioctl SIOCSIFFLAGS error");
	}
	return 0;
}

/*set ip address*/
int set_if_ip(char *if_name, char *ip_str){
	struct ifreq ifr;
	struct sockaddr_in ip_addr;
	int sockfd;

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
		err_sys("socket error");
	}

	ip_addr.sin_family = AF_INET;
	if(inet_pton(AF_INET, ip_str, &ip_addr.sin_addr) < 1){
		err_sys("error ipv4 addr");
	}
	
	strcpy(ifr.ifr_name, if_name);
	memcpy(&ifr.ifr_addr, &ip_addr, sizeof(struct sockaddr_in));
	if(ioctl(sockfd, SIOCSIFADDR, &ifr) < 0){
		err_sys("ioctl SIOCSIFADDR error");
	}
	return 0;
}
