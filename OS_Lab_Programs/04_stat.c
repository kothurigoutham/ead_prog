/* 4. stat() system call
   Usage: ./04_stat [filename]   (default file: /etc/passwd) */
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    const char *file = (argc > 1) ? argv[1] : "/etc/passwd";
    struct stat st;

    if (stat(file, &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("File        : %s\n", file);
    printf("Size        : %lld bytes\n", (long long)st.st_size);
    printf("Inode       : %llu\n", (unsigned long long)st.st_ino);
    printf("Hard links  : %lu\n", (unsigned long)st.st_nlink);
    printf("UID / GID   : %u / %u\n", st.st_uid, st.st_gid);
    printf("Blocks      : %lld\n", (long long)st.st_blocks);

    printf("File type   : ");
    if (S_ISREG(st.st_mode))      printf("regular file\n");
    else if (S_ISDIR(st.st_mode)) printf("directory\n");
    else if (S_ISLNK(st.st_mode)) printf("symbolic link\n");
    else if (S_ISCHR(st.st_mode)) printf("character device\n");
    else if (S_ISBLK(st.st_mode)) printf("block device\n");
    else                          printf("other\n");

    printf("Permissions : %c%c%c%c%c%c%c%c%c (octal %o)\n",
           (st.st_mode & S_IRUSR) ? 'r' : '-', (st.st_mode & S_IWUSR) ? 'w' : '-',
           (st.st_mode & S_IXUSR) ? 'x' : '-', (st.st_mode & S_IRGRP) ? 'r' : '-',
           (st.st_mode & S_IWGRP) ? 'w' : '-', (st.st_mode & S_IXGRP) ? 'x' : '-',
           (st.st_mode & S_IROTH) ? 'r' : '-', (st.st_mode & S_IWOTH) ? 'w' : '-',
           (st.st_mode & S_IXOTH) ? 'x' : '-', st.st_mode & 0777);

    printf("Last access : %s", ctime(&st.st_atime));
    printf("Last modify : %s", ctime(&st.st_mtime));
    printf("Last change : %s", ctime(&st.st_ctime));
    return 0;
}
