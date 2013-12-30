/*************************************************************************
	> File Name: web.c
	> Description: web browser.
	> Author: Taylor
	> Mail: 
	> Created Time: 2013年12月20日 星期五 08时48分13秒
 ************************************************************************/
/*include web1*/
#include "web.h"

int main(int argc, char **argv){
	int i, fd, n, maxnconn, flags, error;
	char buf[MAXLINE];
	fd_set rs, ws;

	/*example: ./web 3 192.168.246.175 / /info.html*/
	if(argc<5){
		err_quit("usage: web<#conns> <hostname> <homepage> <file1> ...");
	}
	maxnconn = atoi(argv[1]);/*ascii to integer*/

	nfiles = min(argc-4, MAXFILES);
	for(i = 0; i < nfiles; i++){
		file[i].f_name = argv[i+4];
		file[i].f_host = argv[2];
		file[i].f_flags = 0;
	}
	printf("nfiles = %d\n", nfiles);/*do not include / home page.*/

	/*create TCP connect for home page '/',parameters: domain,file path*/
	home_page(argv[2], argv[3]);
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	maxfd = -1;
	nlefttoread = nlefttoconn = nfiles;
	nconn = 0;
/*end web1*/

/*include web2*/
	while(nlefttoread > 0){
		while(nconn < maxnconn && nlefttoconn > 0){
			/*find a file to read*/
			for(i = 0; i < nfiles; i++)
				if(file[i].f_flags == 0){
					printf("flags=%d\n", file[i].f_flags);
					break;
				}
			if(i==nfiles)
				err_quit("nlefttoconn = %d but nothing found", nlefttoconn);
			start_connect(&file[i]);/*nonblocking connecting start.*/
			nconn++;
			nlefttoconn--;
		}
		printf("nfiles:%d,nconn:%d,maxnconn:%d,nlefttoconn:%d\n", nfiles, nconn, maxnconn, nlefttoconn);/*nconn:2,maxnconn:2,nlefttoconn:1*/
	
		rs = rset;
		ws = wset;
		n = Select(maxfd+1, &rs, &ws, NULL, NULL);

		for(i = 0; i < nfiles; i++){
			flags = file[i].f_flags;
			/*ignore non-connect and read done*/
			if(flags == 0 || flags & F_DONE)
				continue;
			fd = file[i].f_fd;
			/*printf("i=%d\n", i);*/
			if( flags & F_CONNECTING && (FD_ISSET(fd, &rs) || FD_ISSET(fd, &ws)) ){
				n = sizeof(error);
				if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&n) < 0 || error != 0){
					err_ret("nonblocking connect failed for %s", file[i].f_name);
				}
				/*connection established*/
				printf("connection established for %s\n", file[i].f_name);
				FD_CLR(fd, &wset);/*no more writeability test*/
				write_get_cmd(&file[i]);/*write() the GET command*/
			}else if(flags & F_READING && FD_ISSET(fd, &rs)){
				if( (n = Read(fd, buf, sizeof(buf))) ==0 ){
					printf("end-of-file on %s\n\n", file[i].f_name);
					Close(fd);
					file[i].f_flags = F_DONE;/*clears F_READING*/
					FD_CLR(fd, &rset);
					nconn--;
					nlefttoread--;
				}else{
					printf("read %d bytes from %s\n", n, file[i].f_name);
				}
			}else{
				printf("waiting fd=%d\n", fd);
			}
		}
	}
	return 0;
}

void home_page(const char *host, const char *fname){
	int fd, n;
	char line[MAXLINE];

	fd = Tcp_connect(host, SERV);/*blocking connect()*/
	n = snprintf(line, sizeof(line), GET_CMD, fname, host);
	/*printf("buffer n:%d,str:%s\n", n, line);exit(0);*/
	Writen(fd, line, n);
	printf("wrote %d bytes for filename '%s'\n", n, fname);
	printf("%s", line);
	for(;;){
		if( (n = Read(fd, line, MAXLINE)) == 0)
			break;/*server closed connection*/
		else
			printf("%s",line);
		printf("read %d bytes of home page\n", n);
		/*do whatever with data*/
	}
	printf("end-of-file on home page\n\n");
	Close(fd);
}

void start_connect(struct file *fptr){
	int fd, flags, n;
	struct addrinfo *ai;

	ai = Host_serv(fptr->f_host, SERV, 0, SOCK_STREAM);

	fd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	fptr->f_fd = fd;
	printf("start_connect for %s, fd %d\n", fptr->f_name, fd);

	/*set socket nonblocking*/
	flags = Fcntl(fd, F_GETFL, 0);
	Fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	/*initiate nonblocking connect to the server.*/
	if( (n = connect(fd, ai->ai_addr, ai->ai_addrlen))<0 ){
		if(errno != EINPROGRESS)
			err_sys("nonblocking connect error");
		else
			printf("nonblocking connect fd %d\n", fd);
		fptr->f_flags = F_CONNECTING;
		FD_SET(fd, &rset);/*select for reading adn writing*/
		FD_SET(fd, &wset);
		if(fd > maxfd)
			maxfd = fd;
	}else if(n >= 0) /*connect is already done*/
		write_get_cmd(fptr);/*write() the GET command*/
}

void write_get_cmd(struct file *fptr){
	int n;
	char line[MAXLINE];

	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name, fptr->f_host);
	Writen(fptr->f_fd, line, n);
	printf("wrote %d bytes for %s\n", n, fptr->f_name);
	printf("%s", line);

	fptr->f_flags = F_READING;/*clears F_CONNECTING*/
	FD_SET(fptr->f_fd, &rset);/*will read server's reply*/
	if(fptr->f_fd > maxfd)
		maxfd = fptr->f_fd;
}


