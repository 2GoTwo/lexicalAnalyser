#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wfAl.h"
FILE* source;
int main(int argc, char const *argv[])
{
	source = openFile(argv[1]);
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
FILE* openFile(const char* path){
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL)
	{
		printf("%s\n", "cannot open file");
        exit(1);
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
	uniLex* uniLex = initializeUniLex();
	char c;
	c = readChar(); /* state 0 */
	while(isWhite(c)){
		c = readChar();
	}
	/* === operators === */
	if (c == '<') {
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
            recule(c); /* state = 4 */
            strcpy(uniLex->name, "OPERL");
            strcpy(uniLex->value, "INF");
            return uniLex;
        }
    }
    else if(c == '>')
    {
    	c = readChar(); 
    	if( c == '=')
    	{
    		/* state 5 */
    		strcpy(uniLex->name,"OPERL");
    		strcpy(uniLex->value,"SUPEG");
    		return uniLex;
    	}
    	else{
    		/* state 6 */
    		recule(c);
    		strcpy(uniLex->name,"OPERL");
    		strcpy(uniLex->value,"SUP");
    		return uniLex;
    	}
    }
    /* === operators === */

    /* === identifiers === */
    /* state 0 */
    if(isLetter_(c))
    {
    	/* state 7 */
    	int index = 0;
    	char idName[IDENIFIER_MAX_LENGHT];
    	while(isLetter_(c) || isDigit(c)){
    		idName[index++] = c;
    		c = readChar();
    	}
    	/* state 8 */
    	recule(c);
        idName[index] = '\0';
        int nbrKeyWord = sizeof KeyTab / sizeof KeyTab[0];
        for(int i=0;i<nbrKeyWord;i++)
        {
            if(strcmp(idName,KeyTab[i].name) == 0)
            {
                return &KeyTab[i];
            }
        }
        strcpy(uniLex->name,"ID");
        strcpy(uniLex->value,idName);
    	return uniLex;
    }
    /* === identifiers === */

    /* === numbers === */
    /* state 0 */
    if(isDigit(c))
    {
    	/* state 9 */
    	strcpy(uniLex->name,"NUMBER");
    	int index = 0;
    	char number[NUMBER_MAX_LENGHT];
    	while(isDigit(c))
    	{
    		number[index++] = c;
    		c = readChar();
    	}
    	if(c == 'e' || c== 'E') /* state 10 */
    	{
    		number[index++] = c;
    		c = readChar();
    		if(isDigit(c)) /* state 14 */
    		{
    			while(isDigit(c))
    			{
    				number[index++] = c;
    				c = readChar();
    			}
    			/* state 15 */
                number[index] = '\0';
    			recule(c);
    		}
    		else if(c == '-') /* state 11 */
    		{
    			number[index++] = c;
    			c= readChar();
    			if(isDigit(c))  /* state 12 */
    			{
    				while(isDigit(c))
    				{
    					number[index++] = c;
    					c = readChar();
    				}
    				/* state 13 */
                    number[index] = '\0';
    				recule(c);
    			}
    		}
    	}
    	else if(c == '.'){ /* state 16 */
    		number[index++] = c;
    		c = readChar();
    		if (isDigit(c)) /* state 17 */
    		{
    			while(isDigit(c))
    			{
    				number[index++] = c;
    				c = readChar();
    			}
                number[index] = '\0';
    			recule(c);
    			/* state 18 */
    		}
    	}
    	else{
    		/* state 19 */
    		recule(c);
    	}
        number[index] = '\0';
    	strcpy(uniLex->value,number);
    	return uniLex;
    }
    /* === numbers === */
    return NULL;
}





