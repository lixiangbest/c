/*************************************************************************
	> File Name: 18/getroute.c
	> Description: linux get route, equal to 'netstat -r'
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月25日 星期三 02时50分16秒
 ************************************************************************/
#include "unp.h"
/*start route.h*/
#ifndef _ROUTE_H
#define _ROUTE_H
struct r_entry{
	int dest;
	int mask;
	int gateway;
	char interface[10];
	struct r_entry *next;
};
#endif
/*end route.h*/

#define PATH "/proc/net/route"

/*
 * open the /proc/net/route file and get the route entry
 * return: e r_entry linklist if success, or a NULL pointer if failed
 */
struct r_entry *get_route_entry(void){
	FILE *fp = NULL;
	char buf[BUFSIZ] = {'\0'};
	int first_time = 1;
	int first_line = 1;
	int no_use;
	struct r_entry *head, *q, *p;

	fp = fopen(PATH, "r");
	if(fp == NULL){
		err_quit("can't open file: %s", PATH);
	}

	head = q = p = NULL;
	while(!feof(fp)){
		if( fgets(buf, BUFSIZ, fp) == NULL ){
			continue;
		}
		//printf("buf:%s\n",buf);
		if(first_line){
			first_line = 0;
			continue;
		}

		p = Malloc(sizeof(struct r_entry));
		sscanf(buf, "%s%x%x%x%x%x%x%x", p->interface, &p->dest, &p->gateway, &no_use, &no_use, &no_use, &no_use, &p->mask);
		p->next = NULL;

		/*add to link*/
		if(first_time){
			head = p;
			q = p;
			first_time = 0;
		}else{
			q->next = p;
			q = q->next;
		}
	}
	fclose(fp);

	return head;
}

int del_route_entry(struct r_entry *head){
	struct r_entry *q, *p;

	if(head == NULL)
		return 0;

	p = q = head;
	for(p = q = head; p!=NULL; p = q){
		q = p->next;
		free(p);
	}
	return 0;
}

/*display route table*/
int display_route(void){
	struct r_entry *head, *p;
	char buf1[20] = {'\0'};
	char buf2[20] = {'\0'};
	char buf3[20] = {'\0'};
	struct in_addr gateway;/*32 IP address, network byte order*/
	struct in_addr dest;
	struct in_addr netmask;

	head = get_route_entry();/*get the route table*/
	if(head == NULL){
		err_quit("can not get route table\n");
	}

	printf("Iface\tDestination\tGateway\tNetmask\n");
	memset(&gateway, 0, sizeof(struct in_addr));
	memset(&dest, 0, sizeof(struct in_addr));
	for(p = head; p!=NULL; p = p->next){
		gateway.s_addr = p->gateway;
		dest.s_addr = p->dest;
		netmask.s_addr = p->mask;
		printf("%s\t%s\t%s\t%s\n", p->interface, inet_ntop(AF_INET, &dest, buf1, 20), inet_ntop(AF_INET, &gateway, buf2, 20), inet_ntop(AF_INET, &netmask, buf3, 20));
	}
	del_route_entry(head);
	return 0;
}

int main(int argc, char **argv){
	printf("#define BUFSIZ: %d\n", BUFSIZ);
	display_route();
	return 0;
}


