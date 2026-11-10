/* 3. setenv() and getenv() */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *v = getenv("MY_VAR");
    printf("Before setenv : MY_VAR = %s\n", v ? v : "(not set)");

    if (setenv("MY_VAR", "Hello_OS_Lab", 1) != 0) {
        perror("setenv");
        return 1;
    }
    v = getenv("MY_VAR");
    printf("After setenv  : MY_VAR = %s\n", v ? v : "(not set)");

    /* overwrite = 0 -> existing value is NOT changed */
    setenv("MY_VAR", "Other_Value", 0);
    printf("overwrite = 0 : MY_VAR = %s\n", getenv("MY_VAR"));

    /* overwrite = 1 -> value is changed */
    setenv("MY_VAR", "Other_Value", 1);
    printf("overwrite = 1 : MY_VAR = %s\n", getenv("MY_VAR"));

    char *home = getenv("HOME");
    printf("HOME          = %s\n", home ? home : "(not set)");
    char *path = getenv("PATH");
    printf("PATH          = %s\n", path ? path : "(not set)");
    return 0;
}
