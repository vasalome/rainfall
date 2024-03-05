#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int p()
{
    void *eip;
    char buffer[76];

    fflush(stdout);
    gets(buffer);
    if (((unsigned int)eip & 0xb0000000) == 0xb0000000)
    {
        printf(eip);
        _exit(1);
    }
    puts(buffer);
    strdup(buffer);
    return (0);
}

int main(void)
{
    p();
    return (0);
}