#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<signal.h>
#include<stdlib.h>
#define BUFSIZE 1024

//l'azione assogiata al segnale va gestita dal processo che riceve il segnale (deve fare sigaction)

static int bit;
sigset_t usr12mask;  //rappresenta un insieme di segnali
void usr12action(int num, siginfo_t *info, void *useless) {
	bit = (num == SIGUSR2);
	//printf("GOT %d from %d\n",bit,info->si_pid);
	printf("GOT %d\n",bit);  //nuova riga
	kill(info->si_pid, SIGUSR1);
}

int readbit(void *v)
{
	sigsuspend(&usr12mask); //aspetta finché non arriva un segnale che non è in usr12mask
	return bit;
}

int bin2char(int (*f)(void *opaque), void *opaque) {
	int i;
	int c;
	for (i=c=0; i<8; i++) {
		int n=f(opaque);
		if (n<0)
			return -1;
		c = c<<1 | n;
	}
}

//main era void

int main(int argc, char *argv[]) {
	int c;
	static struct sigaction sa={
		.sa_sigaction=usr12action,
		.sa_flags=SA_SIGINFO
	};
	printf("%d\n",getpid());

	sigfillset(&usr12mask);       //inizializza includendo tutti i segnali 	
	sigdelset(&usr12mask,SIGINT); //elimina SIGINIT dall'insieme dei segnali
	sigprocmask(SIG_SETMASK,&usr12mask,NULL); //nuova riga
	sigdelset(&usr12mask,SIGUSR1); //elimina SIGUSR1 e SIGUSR2 dall'insieme dei segnali
	sigdelset(&usr12mask,SIGUSR2);
	sigaction(SIGUSR1,&sa,NULL);
	sigaction(SIGUSR2,&sa,NULL);

	while ((c=bin2char(readbit,stdin)) != EOF)
		putchar(c);
	return 0;
}
