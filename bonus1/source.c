#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv) {
  int		ret;
  char	buffer[40];
  int 	nb;

  nb = atoi(argv[1]);
  if (!(nb <= 9))
    return(1);
  memcpy(buffer, argv[2], nb * 4);
  if (nb == 0x574f4c46)
    execl("/bin/sh","sh",0);
  return(0);
}