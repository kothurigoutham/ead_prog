/* 7. open() system call */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    /* 1. create a new file (O_CREAT) */
    int fd = open("open_demo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open (create)"); return 1; }
    printf("File created/opened for writing, file descriptor = %d\n", fd);
    write(fd, "Hello open()\n", 13);
    close(fd);

    /* 2. open existing file read-only */
    fd = open("open_demo.txt", O_RDONLY);
    if (fd < 0) { perror("open (read-only)"); return 1; }
    printf("File opened for reading,  file descriptor = %d\n", fd);
    char buf[50];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    buf[n > 0 ? n : 0] = '\0';
    printf("Content read: %s", buf);
    close(fd);

    /* 3. append mode */
    fd = open("open_demo.txt", O_WRONLY | O_APPEND);
    if (fd < 0) { perror("open (append)"); return 1; }
    write(fd, "Appended line\n", 14);
    close(fd);
    printf("Appended a line using O_APPEND.\n");

    /* 4. opening a file that does not exist -> error */
    fd = open("no_such_file.txt", O_RDONLY);
    if (fd < 0)
        printf("Opening 'no_such_file.txt' failed: %s (errno = %d)\n", strerror(errno), errno);
    return 0;
}
