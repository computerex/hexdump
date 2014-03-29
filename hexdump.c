#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
   FILE * file;
   size_t size;
   unsigned char * filecontent=0, *bp;
   char buffer[32];
   unsigned int count, i;
   if ( argc < 2 ) {
        printf("usage: %s filename\n", argv[0]);
		return 1;
	}
	file = fopen(argv[1], "rb");
	fseek(file, 0, SEEK_END);
	size=ftell(file);
	fseek(file, 0, SEEK_SET);
	filecontent = (char*)malloc(size);
	if ( filecontent == 0 ) {
		printf("heap error, terminating...\n");
		return 1;
	}
	fread(filecontent, 1, size, file);
	fclose(file);
	file=fopen("output.hex", "w");
	// 10 bytes per line for nice output
	count=i=0;
	bp=filecontent;
	while(count<size){
		for ( i = 0; i < 10; i++ ){
			if ( count+i >= size ) break;
			sprintf(buffer, "%02x ", *bp++);
			fputs(buffer, file);
		}
		count+=10;
		strcpy(buffer, "\n");
		fputs(buffer, file);
	}
	fclose(file);
	free(filecontent);
    return 0;
}