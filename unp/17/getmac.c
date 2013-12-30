/*************************************************************************
	> File Name: 17/getmac.c
	> Description:ioctl to get MAC address
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月22日 星期日 18时59分05秒
 ************************************************************************/
#include "unpifi.h"

int main(int argc, char **argv){
	struct sockaddr_in *addr;
	struct ifreq ifr;
	unsigned char *mac;
	char *address;
	int sockfd;
	if(argc < 2){
		err_quit("Usage: interface<eth0 or lo>");
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);
	if(ioctl(sockfd, SIOCGIFADDR, &ifr) == -1){
		err_sys("IFADDR ioctl error");
	}
	addr = (struct sockaddr_in *)&(ifr.ifr_addr);
	address = inet_ntoa(addr->sin_addr);
	printf("inet addr: %s\n", address);
	
	if(ioctl(sockfd, SIOCGIFHWADDR, &ifr) == -1){
		err_sys("HWADDR ioctl error");
	}
	mac = (unsigned char *)(ifr.ifr_hwaddr.sa_data);
	printf("mac address: %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	printf("%d: [%s]----\n", strlen(mac), mac);

	return 0;
}

