#include <stdio.h>
#define version "sloccy version 0.0.1, https://modula.dev"
#define config_name "/usr/local/etc/sloccy.txt"
#define true -1
#define false 0
#define bool int

int noColor = false;
int shallowSearch = false;

#include "string.c"
#include "file.c"
#include "ansi.c"
#include "ext.c"
#include "dir.c"
#include "count.c"
#include "generated/config.h"
#include "generated/help.h"

void sloc(lconf_t *lconf, char *filename) {
    char *extension = getExt(filename); if (extension == NULL) { return; }
    int language = matchExt(lconf, extension); if (language == false) { return; }
    count(lconf, filename, language); lconf->language[language].files++;
}

void search(lconf_t *lconf, char *path) {
    //printf("    ... searching %s\n", path);
    char **directories;
    char **files; int i;
    char fullPath[1024] = { 0 };
    if ( shallowSearch == false ) {
        directories = getDirectories(path);
        for(i=0; directories[i] != NULL; i++) {
            sprintf(fullPath, "%s/%s", path, directories[i]);
            search(lconf, fullPath);
        }
        free(directories);
    }
    //printf("       -> checking regular files in %s\n", path);
    files = getFiles(path);
    i=0; while( files[i] != NULL ) {
        sprintf(fullPath, "%s/%s", path, files[i]);
        sloc(lconf, fullPath);
        i++;
    }
    free(files);
}

int main(int argc, char **argv){
    char *main = argv[0];
    char *path;
    int result = 1;
    lconf_t *lconf;
    if ( argc > 1 ) {
    if (argv[1][0] == '-') {
        switch(argv[1][1]){
            case 'c': lconf = loadLanguages(); printLanguages(lconf); exit(false);
            case 'v': printf("%s\n", version); exit(false);
            case 'h': printf("%s\n%s\n", version, help); exit(false);
            case 'r':
                result = file_write(config_name, config, config_len);
                if (result == false) { printf("Unable to write to config file (%s), try running with sudo\n", config_name); exit(true); }
                exit(false);
            case 's':
                shallowSearch = true; result++; break;
            case 'n': noColor = true; result++; break;
            default:
                printf("%s\n%s\n", version, help); exit(true);
        }
    }}
    if (path == NULL ) {
        if ( argc > result ) { path = argv[result]; }
        else { path = malloc(sizeof(char)*1024); getcwd(path, 1024); }
    }
    lconf = loadLanguages();
    //printf(green"%s"white"\n", path);
    search(lconf, path);
    printResults(lconf);
}