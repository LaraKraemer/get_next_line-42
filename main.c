#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


/* int main()
{
    int     fd;
    char    buf[256];
    int     char_read;

    fd = open("file2.txt", O_RDWR | O_CREAT);
    printf("fd of file %d", fd);
    return (0);
}

int main()
{
    int fd;

    fd = open("file.txt", O_RDWR | O_CREAT);
    printf("fd of file %d", fd);
    dup2(fd, 1);
    write(1, "hello\n", 6);
    write(fd, "hello\n", 6);
    return (0);
} */