#define lineScalar 48
int calcScore(int filesize, int whitespace, int lines) {
    int semantic = filesize - ( whitespace + lines );
    int score = semantic / lineScalar;
    return score;
}

#define maxFileSize 1024 * 1024 * 4
char fileBuffer[maxFileSize] = { 0 };
void count(lconf_t *lconf, char *filename, int ext){
    int whitespace = 0; int lines = 0;
    int handle = file_read(filename, &fileBuffer, maxFileSize-1);
    int i; for(i=0; i<handle; i++) {
        switch(fileBuffer[i]){
            case ' ': case '\r': case '\t': whitespace++; break;
            case '\n': lines++; break;
            case ';': if (trueLinebreaks == false) { lines++; } else { whitespace++; } break;
            default: break;
        }
    }
        lconf->language[ext].chars += handle - whitespace - lines;
    if ( handle > 0 ) {
        lconf->language[ext].lines += lines + 1;
        lconf->language[ext].score += calcScore(handle, whitespace, lines);
    }
}