#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<signal.h>
#include<stdlib.h>
#define BUFSIZE 1024

//l'azione assogiata al segnale va gestita dal processo che riceve il segnale (deve fare sigaction)


sigset_t usr1mask;

void usr1action(int num, siginfo_t *info, void *useless) {      // perché è qui? Cosa fa? 
}

void printbin(int i,void *v)
{
	pid_t *rec=v;
//	printf("%d %d\n",*rec,i?SIGUSR2:SIGUSR1);
	printf("%d %d\n",*rec,i?SIGUSR2:SIGUSR1); //riga nuova
	kill(*rec,i?SIGUSR2:SIGUSR1);
	sigsuspend(&usr1mask);
	 printf("GOT ACK\n"); //riga nuova
}

void char2bin(unsigned char x, void (*f)(int i,void *opaque),void *opaque) //perché c'è l'ultimo void *opaque?
{
	unsigned int i;
	for (i=0x80; i>0; i>>=1)
		f(!!(x & i),opaque);
}

//il main prima era void, ora è diventato int

int main(int argc, char *argv[]) {
	unsigned char buf[BUFSIZE];
	unsigned char *s;

	//static struct sigaction sa={.sa_sigaction=usr1action};
	static struct sigaction sa={.sa_sigaction=usr1action,.sa_flags=SA_SIGINFO};
	sigaction(SIGUSR1,&sa,NULL);

	printf("%d\n",getpid());
	sigfillset(&usr1mask);
	sigdelset(&usr1mask,SIGINT);    // SIGINT sta per "program interrupt" di default termina il programma
	sigprocmask(SIG_SETMASK,&usr1mask,NULL); 
	sigdelset(&usr1mask,SIGUSR1);
	if (argc>1) {
		pid_t receiver=atoi(argv[1]);
		while ((s=fgets(buf,BUFSIZE,stdin))!=NULL) {
			while (*s)
				char2bin(*s++,printbin,&receiver);
		}
	}
	printf("\n");
	return 0;
}
