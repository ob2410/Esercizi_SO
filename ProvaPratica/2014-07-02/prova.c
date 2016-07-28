#include <stdio.h>

int main (int argc, char *argv[]){
	FILE *fp;
	char *txt= "sto provando\n";
	fp=fopen("ciao", "a");
	for (int i=0; i<4; i++) {
	
		fwrite(txt, 1, sizeof(txt), fp);
	
	}
	fclose(fp);

	return 0;
}
