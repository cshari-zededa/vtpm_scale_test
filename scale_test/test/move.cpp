#include <iostream>
#include <unistd.h>

int main (int argc, const char *argv[])
{
	int rc = 0;
        const char *path[4] = {"/bin/mv", argv[2], argv[4]};
	path[3] = NULL;
        if (execve(path[0], (char **)&path, NULL) != 0) {
		perror("exeve():");
	}
 	return rc;
}
