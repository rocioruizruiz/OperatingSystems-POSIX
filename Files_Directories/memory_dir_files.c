#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#ifndef NAME_MAX
#define NAME_MAX 1024
#endif

static long recursive_search(char *dirname){

    DIR *dir = opendir(dirname);
    if (dir == 0){ // Si no existe devuelve 0
        exit(-1);
    }

    struct dirent *dit;
    struct stat st;
    long size = 0;
    long total_size = 0;
    char filePath[NAME_MAX];

    while ((dit = readdir(dir)) != NULL){
        if ((strcmp(dit->d_name, ".") == 0) || (strcmp(dit->d_name, "..") == 0)){
            continue;
        }
            
        sprintf(filePath, "%s/%s", dirname, dit->d_name);
        if (lstat(filePath, &st) != 0){
            continue;
        }

        size = st.st_size;

        if (S_ISDIR(st.st_mode)){
            long dir_size = recursive_search(filePath) + size;
            printf("DIR\t");
            printf("SIZE: %ld\n", dir_size);
            total_size += dir_size;
        }else{
            total_size += size;
            printf("FILES\t");
            printf("SIZE: %ld\n", size);
        }
    }
    return total_size;
}

int main(int argc, char *argv[]){
    if (argc != 2){ // Si no tiene argumentos o mas de uno error
        perror("Ninguno o demasiados argumentos");
    }

    long size = recursive_search(argv[1]); // retorna el size de la bsuqueda
    printf("Total size: %ld Bytes\n", size);

    return 0;
}