/* 5. write() system call */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    const char *msg = "Hello from the write() system call!\n";

    /* file descriptor 1 = standard output */
    ssize_t n = write(1, msg, strlen(msg));
    printf("Bytes written to screen: %zd\n", n);

    /* write into a file */
    int fd = open("write_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    const char *text = "This line was written to a file using write().\n";
    n = write(fd, text, strlen(text));
    if (n < 0) {
        perror("write");
        close(fd);
        return 1;
    }
    printf("Bytes written to file  : %zd (file: write_output.txt)\n", n);
    close(fd);
    return 0;
}
