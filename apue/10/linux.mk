include ../Make.defines.linux

PROGS = 01_sigusr 02_reenter 03_child 03_cld 04_kill\
		05_sleep tsleep2 07_read 08_read 09_setops\
		10_critical 11_mask 12_suspend 13_suspend\
		systest 14_sigtstp sig2str twait looptime\
		sigxfsz fwrite

all: abort.o sleep1.o sleep2.o tsleep2.o ${PROGS}

abort.o: abort.c

sleep1.o: sleep1.c

sleep2.o: sleep2.c

05_sleep: 05_sleep.o sleep1.o
	$(CC) $(CFLAGS) -o 05_sleep 05_sleep.o sleep1.o $(LDFLAGS) $(LDLIBS)

tsleep2: tsleep2.o sleep2.o
	$(CC) $(CFLAGS) -o tsleep2 tsleep2.o sleep2.o $(LDFLAGS) $(LDLIBS)

systest: system.o systest.o
	$(CC) $(CFLAGS) -o systest system.o systest.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f ${PROGS} *.o
