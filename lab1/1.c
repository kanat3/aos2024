#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(int argc, char** argv) {
	int res = rmdir("test_path.test");

	perror("this is message to describe errno");
	printf("errno: %d\n", errno);
	printf("strerror(%d): %s", errno, strerror(errno));
	return 0;
}
