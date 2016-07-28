#include <stdio.h>

void printbin(int i)
{
	printf("%d\n",i);
}

void char2bin(unsigned char x, void (*f)(int i))
{
	unsigned int i;
	for (i=0x80; i>0; i>>=1)
		f(!!(x & i)); 
	
	
}

void main(int argc, char *argv[]) {
	if (argc>1) {
		while (*argv[1]) {
			char2bin((unsigned char)*(argv[1]++),printbin);
		}
		
	}
	printf("\n");
}
