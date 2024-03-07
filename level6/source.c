#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int    n()
{
    system("/bin/cat /home/user/level7/.pass");
    return (0);
}

int    m()
{
    puts("Nope");
    return (0);
}

int     main(int argc, char **argv)
{
    char    *str;
    void    (*func)(void);


    arg = malloc(64);
    func = malloc(4);
    *func = m;
    strcpy(str, argv[1]);
    func()
    return (0);
}