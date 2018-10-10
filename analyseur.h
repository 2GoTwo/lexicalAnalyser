#ifndef analyseur
#define analyseur

/* === define === */
#define bool int
#define TRUE 1
#define FALSE 0
#define isWhite(c) (c == ' ' || c == '\t' || c == '\n')
#define isLetter_(c) ('A' <= (c) && (c) <= 'Z' || 'a' <= (c) && (c) <= 'z' || '_')
#define isNumber(c) ('0' <= (c) && (c) <= '9')

/* === structure === */
typedef struct uniLex {
	char name[8];
	char value[8];
} uniLex;


/* === methods === */
FILE* openFile(char* path);
char readChar(void);
void recule(char c);
uniLex* initializeUniLex(void);
uniLex* nextUniLex(void);
#endif



