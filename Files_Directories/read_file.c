
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>


int main(){

    int fd;
    char buf[1000];
    size_t nbytes = 1000;
    int bytes_read;

    if((fd = open ("./Practica5/archivo.txt", O_RDONLY, 444))== -1)
        perror("No se ha podido abrir");
    else
        bytes_read = read(fd, buf, nbytes);

    for(int i = 99; i<=108;i++){
        printf("%c", buf[i]);
    }
    
    close(fd); 

    exit(0);
}
