#include <dirent.h>
int maxLocalFiles = 1024;
char **getFiles (char *path) {
    char **self = malloc(sizeof(void*) * maxLocalFiles);
    DIR *dir; struct dirent *entry; int entries = 0;
    dir = opendir(path);
    if ( !dir ) { printf("unable to open directory %s\n", path); exit(true); }
    while ( (entry = readdir(dir))!= NULL ) {
        if ( entry->d_type == DT_REG ) {
            self[entries] = strdup(entry->d_name);
            entries++;
            if (entries >= maxLocalFiles) { maxLocalFiles *= 2; self = realloc( self, sizeof(void*) * maxLocalFiles ); }
        }
    }   closedir(dir);
    self[entries] = NULL;
    return self;
}

char **getDirectories (char *path) {
    char **self = malloc(sizeof(void*) * maxLocalFiles);
    DIR *dir; struct dirent *entry; int entries = 0;
    dir = opendir(path);
    if ( !dir ) { printf("unable to open directory %s\n", path); exit(true); }
    while ( (entry = readdir(dir))!= NULL ) {
        if ( entry->d_type == DT_DIR ) {
            if ( strncmp(entry->d_name, ".", 2) == true || strncmp(entry->d_name, "..", 3) == true ) { continue; }
            self[entries] = strdup(entry->d_name);
            entries++;
            if (entries >= maxLocalFiles) { maxLocalFiles *= 2; self = realloc( self, sizeof(void*) * maxLocalFiles ); }
        }
    }   closedir(dir);
    self[entries] = NULL;
    return self;
}