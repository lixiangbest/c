/*************************************************************************
	> File Name: test.c
	> Description: 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月22日 星期日 13时58分08秒
 ************************************************************************/
#include "unpifi.h"

#ifdef HAVE_SOCKADDR_SA_LEN
int is_len = 1;
#else
int is_len = 0;
#endif

#ifdef IPV6
int is_ipv6 = 1;
#else
int is_ipv6 = 0;
#endif

#ifdef HAVE_SOCKADDR_DL_STRUCT
int is_dl = 1;
#else
int is_dl = 0;
#endif

#ifdef SIOCGIFBRDADDR
int is_brd = 1;
#else
int is_brd = 0;
#endif

#ifdef SIOCGIFDSTADDR
int is_dst = 1;
#else
int is_dst = 0;
#endif

int main(){

	printf("HAVE_SOCKADDR_SA_LEN:%d\n", is_len);
	printf("IPV6:%d\n", is_ipv6);
	printf("HAVE_SOCKADDR_DL_STRUCT:%d\n", is_dl);

	printf("IFI_NAME:%d, IFNAMSIZ:%d\n", IFI_NAME, IFNAMSIZ);

	printf("SIOCGIFBRDADDR:%d\n", is_brd);

	printf("SIOCGIFDSTADDR:%d\n", is_dst);

	return 0;
}

