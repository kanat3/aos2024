#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int get_permission_flag(const char *permission_codes) {
    int r = strstr(permission_codes, "r") > 0;
    int w = strstr(permission_codes, "w") > 0;

    if (r && w) return O_RDWR;
    else if (r) return O_RDONLY;
    else if (w) return O_WRONLY;
    else return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file [r|w]+\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int permission_flag = get_permission_flag(argv[2]);

    int fd = open(filename, O_CREAT | permission_flag, 0444);

    const char * msg = "abc\nabc\nabc";
    write(fd, msg, strlen(msg));
    close(fd);

    fd = open(filename, O_RDONLY);
    char buf[1024];
    int r = read(fd, buf, strlen(msg)*sizeof(char));
    if (r < 0) { 
        printf("Unable to read\n");
    } else {
        buf[strlen(msg)] = '\0'; /* cut stuff after msg */
        printf("Message:\n%s\n(read %d bytes)\n", buf, r);
    }
    close(fd);

    fd = open(filename, O_RDWR);
    perror("open");
    printf("errno: %d\n", errno);
    printf("strerror(%d): %s\n", errno, strerror(errno));
    if (fd >= 0) close(fd);
    exit(0);
}

