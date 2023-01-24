#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>
#define _GNU_SOURCE
	
int main(int argc, char **argv)
{
	char *sh;
	gid_t gid;
	uid_t uid;
	char *arg[2];
	
	if (atoi(argv[1]) != 0x1a7)
        fwrite("No !\n", 1, 5, stderr);
    else
	{
        sh = strdup("/bin/sh");
        
        gid = getegid();
        uid = geteuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        // setregid(gid, gid);
        // setreuid(uid, uid);

        arg[0] = "sh";
        arg[1] = NULL;
        execv("/bin/sh", arg);
	}
}