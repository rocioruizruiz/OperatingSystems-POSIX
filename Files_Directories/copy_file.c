
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>



int main(){

    int fd, fd2;
    char buf[1000];
    size_t nbytes = 1000;
    int bytes_read;

    if((fd = open ("./Practica5/archivo.txt", O_RDONLY, 444))== -1)
        perror("No se ha podido abrir");
    else
        bytes_read = read(fd, buf, nbytes);
    
    close(fd);
    if((fd2 = open ("./Practica5/archivo2.txt", O_RDWR | O_CREAT, 111))== -1)
        perror("No se ha podido abrir");
    else
        write(fd2, buf, bytes_read);

    return 0;
}

