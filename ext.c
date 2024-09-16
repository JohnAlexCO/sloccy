#define language_max    64
#define language_maxlen 32
#define language_maxext 32
#define language_buf    1024 * 1024
typedef struct {
    char name[language_maxlen]; int entries;
    char *extensions[language_maxext];
    int lines; int chars; int files; int score;
} language_t;
typedef struct {
    int entries; language_t language[language_max];
} lconf_t;

language_t *initLanguage(lconf_t *L, char *name){
    language_t *self = &(L->language[L->entries]);
    strncpy(self->name, name, language_maxlen);
    self->entries = 0;
    self->score = 0; self->lines = 0; self->chars = 0; self->files = 0;
    L->entries++;
    return self;
}

void *extLanguage(language_t *L, char *ext) {
    if (ext[0] == 0) { return NULL; }
    if (language_maxext <= L->entries) {
        printf(red"extLanguage "white"(%s, \"%s\") [%hhx] Contains %d entries, Unable to add more than %d file extensions\n", L->name, ext, ext[0], L->entries, language_maxext-1); exit(true); }
    L->extensions[L->entries] = ext;
    L->entries++; return L;
}

int matchExt(lconf_t *languages, char *ext) {
    int i; int j;
    for(i=0;i<language_max;i++) {
        if (languages==NULL) { return -1; }
        for(j=0; j < languages->language[i].entries; j++) {
            if (strncmp(languages->language[i].extensions[j], ext, language_maxlen)==true) { return i; }
        }
    }   return -1;
}

lconf_t *loadLanguages() {
    lconf_t *result = malloc(sizeof(lconf_t)); result->entries = 0;
    char *buffer = malloc(sizeof(char)*language_buf);
    int handle = file_read(config_name, buffer, language_buf);
    if (handle == false) { printf("Unable to read config (%s), check the file's permissions\n", config_name); exit(true); }
    int c=0; int n; bool top = true; language_t *L;
    while ( buffer[c] != 0 && c < handle ) {
        if (top == true) {
            switch(buffer[c]) {
                case 0: return result;
                case ' ': case '\r': case '\n': c++; break;
                default:
                    n = wordSize(buffer+c);
                    L = initLanguage(result, slice(buffer+c, n));
                    c += n; top = false;
                    break;
            }
            continue;
        }
        else {
            switch(buffer[c]) {
                case 0: return result;
                case ' ': case '\r': case '\n': c++; break;
                case ';': top = true; c++; break;
                default:
                    if (L == NULL) { printf("config error, cannot extend null char family\n"); exit(true); }
                    n = wordSize(buffer+c);
                    if ( extLanguage(L, slice(buffer+c, n)) == NULL ) { return result; }
                    c += n;
                    break;
            }
            continue;
        }
    }
    return result;
}

void printLanguages(lconf_t *L){
    int i; int j;
    for(i=0; i < L->entries; i++) {
        printf(white "%12s "green" (%d) ",
            L->language[i].name,
            L->language[i].entries);
    for(j=0; j < L->language[i].entries; j++) {
        if (j % 2 == 0) { printf(white "%s ", L->language[i].extensions[j]); }
        else            { printf(blue  "%s ", L->language[i].extensions[j]); }
    }   printf("\n");
    }
}

char *pResultsF =  "    "purple"%12s    "yellow"%d pts  "white"%d files, %d lines, %d chars\n";
char *pResultsBW = "    %12s    %d pts  %d files, %d lines, %d chars\n";
void printResults(lconf_t *L) {
    int i;
    int files = 0; int lines = 0; int chars = 0; int score = 0;
    char *format;
    if ( noColor == true ) { format = pResultsBW; } else { format = pResultsF; }
    for(i=0; i < L->entries; i++) {
        if (L->language[i].files == 0) { continue; }
        else {
            score += L->language[i].score;
            files += L->language[i].files;
            lines += L->language[i].lines;
            chars += L->language[i].chars;
            printf(format,
                L->language[i].name,
                L->language[i].score,
                L->language[i].files,
                L->language[i].lines,
                L->language[i].chars
            );
        }
    }   printf(format, "Total", score, files, lines, chars);
}

char *getExt(char *filename) {
    int dot = nextChar(filename, '.'); if (dot == false) { return NULL; }
    int l = strlen(filename+dot+1);
    return slice(filename+dot+1, l);
}