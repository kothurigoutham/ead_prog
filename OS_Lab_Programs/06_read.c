/* 6. read() system call
   The program first creates a sample file, then reads it back with read(). */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    const char *fname = "read_sample.txt";
    const char *data = "Line 1: Operating Systems Lab\nLine 2: read() system call demo\nLine 3: End of file\n";

    /* create the file */
    int wfd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (wfd < 0) { perror("open (write)"); return 1; }
    write(wfd, data, strlen(data));
    close(wfd);

    /* read the file */
    int fd = open(fname, O_RDONLY);
    if (fd < 0) { perror("open (read)"); return 1; }

    char buf[32];
    ssize_t n;
    long total = 0;
    printf("----- File contents -----\n");
    fflush(stdout);
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(1, buf, n);
        total += n;
    }
    if (n < 0) perror("read");
    fflush(stdout);
    printf("-------------------------\n");
    printf("Total bytes read: %ld\n", total);
    close(fd);
    return 0;
}
