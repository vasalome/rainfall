#include <stdlib.h>
#include <string.h>

char	*p(char *str1, char *str2)
{
	char	buffer[4096];

	puts(str2);
	read(0, buffer, 4096);
	*strchr(buffer, '\n') = 0;
	return (strncpy(str1, buffer, 20));
}

/*
** Buffer size:
** 0x1000 = 4096
** https://fr.calcuworld.com/calculs-mathematiques/calculatrice-hexadecimal/
*/

char	*pp(char *buffer)
{
	char			    input1[20];
	char			    input2[20];
	unsigned int	len;

	p(input1, " - ");
	p(input2, " - ");
	strcpy(buffer, input1);
	len = strlen(buffer);
	buffer[len] = ' ';
	buffer[len + 1] = 0;
	return (strcat(buffer, input2));
}

int		main(void)
{
	char	buffer[42];

	pp(buffer);
	puts(buffer);
	return(0);
}

/*
** Buffer size:
** 64 (0x40) - 22 (0x16) = 42
** https://fr.calcuworld.com/calculs-mathematiques/calculatrice-hexadecimal/
*/