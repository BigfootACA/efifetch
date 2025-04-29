#include"str.h"

__weak int isspace(int c){return c==' '||(unsigned)c-'\t'<5;}
__weak int isalpha(int c){return ((unsigned)c|32)-'a'<26;}
__weak int islower(int c){return (unsigned)c-'a'<26;}
__weak int isupper(int c){return (unsigned)c-'A'<26;}
__weak int tolower(int c){return (isupper(c))?(c|32):c;}
__weak int toupper(int c){return (islower(c))?(c&0x5f):c;}
__weak int isdigit(int c){return (unsigned)c-'0'<10;}
__weak int isprint(int c){return (unsigned)c-' '<0x5f;}