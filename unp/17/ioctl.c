/*************************************************************************
	> File Name: ioctl.c
	> Description: ioctl{SIOCGIFCONF}
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月22日 星期日 21时23分27秒
 ************************************************************************/
#include "unpifi.h"

#define MAX_IFS 64

int main(int argc, char **argv){
	struct ifreq *ifr, *ifend;
	struct ifreq if_req;
	struct ifconf if_conf;
	struct ifreq ifs[MAX_IFS];
	int sockfd;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if_conf.ifc_len = sizeof(ifs);
	if_conf.ifc_req = ifs;
	if(ioctl(sockfd, SIOCGIFCONF, &if_conf) < 0){
		err_sys("ioctl SIOCGIFCONF error");
	}
	ifend = ifs + (if_conf.ifc_len/sizeof(struct ifreq));
	for(ifr=if_conf.ifc_req;ifr<ifend;ifr++){
		if(ifr->ifr_addr.sa_family == AF_INET){
			strncpy(if_req.ifr_name, ifr->ifr_name, sizeof(if_req.ifr_name));
			if(ioctl(sockfd, SIOCGIFHWADDR, &if_req) < 0){
				err_sys("ioctl SIOCGIFHWADDR error");
			}
			printf("Ip address %s\n", inet_ntoa( ((struct sockaddr_in*)&ifr->ifr_addr)->sin_addr ));
			printf("Device %s-> Ethernet %02x:%02x:%02x:%02x:%02x:%02x\n", if_req.ifr_name, 
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[0], 
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[1], 
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[2],
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[3], 
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[4], 
				(int)( (unsigned char *)&if_req.ifr_hwaddr.sa_data)[5]);
		}
	}

	return 0;
}

