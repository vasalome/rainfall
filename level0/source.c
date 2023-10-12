#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>
#define _GNU_SOURCE
	
int main(int argc, char **argv)
{
	gid_t gid;
	uid_t uid;
	char *args[2];

	if (atoi(argv[1]) != 0x1a7)
		fwrite("No !\n", 1, 5, stderr);
	else
	{
		gid = getegid();
		uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);

		args[0] = strdup("/bin/sh");;
		args[1] = NULL;
		execv("/bin/sh", args);
	}
}