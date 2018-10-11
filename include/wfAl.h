#ifndef analyseur
#define analyseur

/* === define === */
#define bool int
#define TRUE 1
#define FALSE 0
#define isWhite(c) (c == ' ' || c == '\t' || c == '\n')
#define isLetter(c) ('A' <= (c) && (c) <= 'Z' || 'a' <= (c) && (c) <= 'z')
#define isUnderscore(c) ((c) == '_')
#define isLetter_(c) (isLetter(c) || isUnderscore(c))
#define isDigit(c) ('0' <= (c) && (c) <= '9')
#define IDENIFIER_MAX_LENGHT 30
#define NUMBER_MAX_LENGHT 30


/* === structure === */
typedef struct uniLex {
	char name[10];
	char value[10];
} uniLex;

uniLex KeyTab[] = {
	{"si",},
	{"sinon",},
	{"entier",},
	{"character",}
};

/* === methods === */
FILE* openFile(const char* path);
char readChar(void);
void recule(char c);
uniLex* initializeUniLex(void);
uniLex* nextUniLex(void);
#endif



