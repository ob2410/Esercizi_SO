#include <stdio.h>

int readbit(void *v)
{
	FILE *f = (FILE *)v;
	int c;
	while ((c=getc(f)) != EOF) {
		switch (c) {
			case '0': return 0;
			case '1': return 1;
		}
	}
	return EOF;
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

void main(int argc, char *argv[]) {
	int c;
	while ((c=bin2char(readbit,stdin)) != EOF)
		putchar(c);
}
