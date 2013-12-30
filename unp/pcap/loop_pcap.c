/*************************************************************************
	> File Name: loop_pcap.c
	> Description: pcap loop. 
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月27日 星期五 16时07分27秒
 ************************************************************************/
#include "unp.h"
#include<netinet/if_ether.h>
#include<pcap.h>

/*callback function that is passed to pcap_loop(..) and called each time a packet is received*/
void my_callback(u_char *useless, const struct pcap_pkthdr *pkthdr, const u_char *packet){
	static int count = 1;
	fprintf(stdout, "%d,", count);
	if(count == 3)
		fprintf(stdout, "Taylor - enchanted");
	if(count == 5)
		fprintf(stdout, "Taylor - timeless");
	fflush(stdout);
	count++;
}

int main(int argc, char **argv){
	//int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr;
	//const u_char *packet;
	//struct pcap_pkthdr hdr;/*pcap.h*/
	//struct ether_header *eptr;/*net/ethernet.h*/

	if(argc != 2){
		fprintf(stdout, "Usage: %s numpackets\n", argv[0]);
		return 0;
	}
	
	/*grab a device to peak into...*/
	if ( (dev = pcap_lookupdev(errbuf)) == NULL ){
		printf("%s\n", errbuf);
		exit(1);
	}

	/*open device for reading*/
	if( (descr = pcap_open_live(dev, BUFSIZ, 0, 0, errbuf)) == NULL ){
		printf("pcap_open_live: %s\n", errbuf);
		exit(1);
	}

	/*
	 * allright here we call pcap_loop(..) and pass in our callback function
	 * int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
	 */
	pcap_loop(descr, atoi(argv[1]), my_callback, NULL);
	
	fprintf(stdout, "\nDone processing packets...\n");
	return 0;
}


