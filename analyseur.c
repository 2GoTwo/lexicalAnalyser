#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur.h"

FILE* source;
int main(int argc, char const *argv[])
{
	source = openFile("file.wf");
	uniLex* u;
	do{
		u = nextUniLex();
		if(u == NULL)
			break;
		printf("<%s,%s>\n", u->name,u->value);
	}while(u != NULL);	
	fclose(source);
	return EXIT_SUCCESS;
}

// to open your file
FILE* openFile(char* path){
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
	{
		printf("%s\n", "cannot open file");
	}
	return fp;
}

char readChar(){
	return getc(source);
}

void recule(char c){
	ungetc(c,source);
}
uniLex* initializeUniLex()
{
	uniLex* u = (uniLex*) malloc(sizeof(uniLex));
	if(u == NULL)
	{
		printf("%s\n", "error while initialize");
		exit(1);
	}
	return u;
}

uniLex* nextUniLex(void){
	char c;
	c = readChar(); /* state 0 */
	while(isWhite(c)){
		c = readChar();
	}
	if (c == '<') {
		uniLex* uniLex = initializeUniLex();
        c = readChar(); /* state = 1 */
        if (c == '='){ /* state = 2 */
			strcpy(uniLex->name, "OPERL");
			strcpy(uniLex->value, "INFEG");
            return uniLex;
        }
        else if (c == '>'){
        	strcpy(uniLex->name,"OPERL");
            strcpy(uniLex->value, "DIFF");
            return uniLex;
        }
        else {
            recule(c); /* etat = 4 */
            strcpy(uniLex->name, "OPERL");
            strcpy(uniLex->value, "INF");
            return uniLex;
        }
    }
    return NULL;
}






