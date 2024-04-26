#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char c[68];

int     m()
{
    time_t  t;

    t = time(0);
    printf("%s - %d\n", (int)t);
    return (0);
}

int     main(int argc, char **argv)
{
    int    *buff1;
    int    *buff2;
    FILE    *fs;

    buff1 = malloc(8);
    buff1[0] = 1;
    buff1[1] = malloc(8);

    buff2 = malloc(8);
    buff2[0] = 2;
    buff2[1] = malloc(8);

    strcpy((char *)buff1[1], argv[1]);
    strcpy((char *)buff2[1], argv[2]);

    fs = fopen("/home/user/level8/.pass", "r");
    fgets(c, 68, fs);
    puts("~~");
    return (0);
}