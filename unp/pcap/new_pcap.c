/*************************************************************************
	> File Name: new_pcap.c
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月27日 星期五 04时21分47秒
 ************************************************************************/
#include "unp.h"
#include<pcap.h> /*if this gives you an error try pcap/pcap.h*/
#include<netinet/if_ether.h> /*include net/ethernet.h*/

int main(int argc, char **argv){
	int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *descr;/*you can man it*/
	const u_char *packet;
	struct pcap_pkthdr hdr;/*pcap.h*/
	struct ether_header *eptr;/*net/ethernet.h*/
	u_char *ptr;/*printing out hardware header info*/
	
	/*grab a device to peak into...*/
	if( (dev = pcap_lookupdev(errbuf)) == NULL ){
		printf("pcap_lookupdev:%s\n", errbuf);
		exit(1);
	}
	printf("DEV:%s\n", dev);
	
	/* 
	 * open the device for sniffing.
	 * pcap_t *pcap_open_live(char *device, int snaplen, int prmisc, int to_ms, char *ebuf)
	 * snaplen - maximum size of packets to capture in bytes
	 * promisc - set card in promiscuous mode?
	 * to_ms - time to wait for packets in miliseconds before read times out
	 * errbuf - if something happens, place error string here
	 *
	 * Note if you change "prmisc" param to anything other than zero, you will get all packets
	 * your device sees, whether they are intendeed for you or not!
	 * Be sure you know the rules of the network you are running on 
	 * before you set your card in promiscuous mode!
	 */
	if( (descr = pcap_open_live(dev, BUFSIZ, 0, 0, errbuf)) == NULL ){
		printf("pcap_open_live:%s\n", errbuf);
		exit(1);
	}
	
	/*
	 * grab a packet from descr(yay!)
	 * u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h)
	 * so just pass in the descriptor we got from our call to pcap_open_live and 
	 * an allocated struct pcap_pkthdr
	 */
	if( (packet = pcap_next(descr, &hdr)) == NULL ){
		/* dinna work *sob* */
		printf("Didn't grab packet\n");
		exit(1);
	}

	/**
	 * struct pcap_pkthdr{
	 *		struct timeval ts; time stamp
	 *		bpf_u_int32 caplen; length of portion present
	 *		bpf_u_int32; lebgth this packet (off wire)
	 * }
	 */
	printf("Grabbed packet of length %d\n", hdr.len);
	printf("Received at ....%s\n", ctime( (const time_t*)&hdr.ts.tv_sec ));
	printf("Ethernet address length is %d\n", ETHER_HDR_LEN);

	/*lets start with the ether header...*/
	eptr = (struct ether_header *)packet;

	/*Do a couple of checks to see what packet type we have.*/
	if(ntohs(eptr->ether_type) == ETHERTYPE_IP){
		printf("Ethernet type hex:%x dec:%d is an IP packet\n", ntohs(eptr->ether_type), ntohs(eptr->ether_type));
	}else if(ntohs(eptr->ether_type) == ETHERTYPE_ARP){
		printf("Ethernet type hex:%x dec:%d is an ARP packet\n", ntohs(eptr->ether_type), ntohs(eptr->ether_type));
	}else{
		printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
		exit(1);
	}

	/*Thank you Richard Stevens!!!RIP*/
	ptr = eptr->ether_dhost;
	i = ETHER_ADDR_LEN;
	printf("Destination Address: ");
	/*printing out hardware header info*/
	do{
		printf("%s%x", (i==ETHER_ADDR_LEN)?"":":", *ptr++);
	}while(--i>0);
	printf("\n");
	
	ptr = eptr->ether_shost;
	i = ETHER_ADDR_LEN;
	printf("Source Address: ");
	do{
		printf("%s%x", (i==ETHER_ADDR_LEN)?"":":", *ptr++);
	}while(--i>0);
	printf("\n");

	return 0;
}

