#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){
    int fd;
    char buf[100];
    mode_t modo = S_IRUSR;
    size_t nbytes = sizeof(buf), bytes_read;

    if((fd = open ("ejemplo", O_RDONLY, modo))== -1)
        perror("No se ha podido abrir");
    else
        bytes_read = read(fd, buf, nbytes);
        printf("%zd bytes leidos \n%s", bytes_read, buf); 
        close(fd);   
    exit(0);
}