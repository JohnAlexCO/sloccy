int strlen(char *str){ int i=0; while(str[i]!=0){i++;} return i; }
bool strncmp(char *dest, char *src, int len) { int i=0; while(dest[i]!=0 && src[i]!=0) { if (dest[i]!=src[i]) { return false; } i++; } return true; }
char *strncpy(char *dest, char *src, int len) { int i=0; while(src[i]!=0 && i<len){ dest[i]=src[i]; i++;} dest[i]=0; return dest; }
char *strcat(char *dest, char *src){
    int dl = strlen(dest); int sl = strlen(src);
    char *result = malloc(sizeof(char)*(dl+sl+1));
    int i; result[dl+sl]=0;
        for(i=0;i<dl;i++) { result[i]=dest[i]; }
        for(i=0;i<sl;i++) { result[dl+i]=src[i]; }
    return result;
}
int nextChar(char *stream, char ref) { int i=0; while(stream[i]!=0) { if (stream[i]==ref) { return i; } i++; } return false; }
char *slice(char *stream, int length) { char *result = malloc(sizeof(char)*length); strncpy(result, stream, length); return result; }
int wordSize(char *stream) {
    int sp = nextChar(stream, ' ');
    int ln = nextChar(stream, '\n');
    int rn = nextChar(stream, '\r');
    int sm = nextChar(stream, ';');
    int z  = nextChar(stream, '\0');
    int yield = false;
    if ( sp != false ) { yield = sp; }
    if ( ln != false && ln < yield ) { yield = ln; }
    if ( rn != false && rn < yield ) { yield = rn; }
    if ( sm != false && sm < yield ) { yield = sm; }
    if ( z  != false && z  < yield ) { yield = z;  }
    return yield;
}