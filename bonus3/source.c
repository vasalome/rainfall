#include <stdio.h>

int	main(int argc, char **argv)
{
	FILE	*stream;
	char	buffer1[66];
	char	buffer2[65];

	stream = fopen("/home/user/end/.pass", "r");
  
	if (!stream || argc != 2)
		return (-1);

	fread(buffer1, 1, 66, stream);
	buffer1[atoi(argv[1])] = "\0";

	fread(buffer2, 1, 65, stream);
	fclose(stream);

	if (strcmp(buffer1, argv[1]) == 0)
		execl("/bin/sh", "sh", 0);
	else
		puts(buffer1[66]);

	return (0);
}