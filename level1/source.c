#include <stdlib.h>
#include <stdio.h>

void run(void)
{
  fwrite("Good... Wait what?\n", 1, 19, stdout);
  system("/bin/sh");
}

int main(int ac, char **av)
{
   char s[76];

   gets(s);
   return (0);
}