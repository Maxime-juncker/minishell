#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int is_fd_open(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

int main() {
    int fd = open("/dev/null", O_RDONLY);
    
    if (is_fd_open(fd)) {
        printf("FD %d is open\n", fd);
    } else {
        printf("FD %d is closed\n", fd);
    }

    close(fd);

    if (is_fd_open(fd)) {
        printf("FD %d is open\n", fd);
    } else {
        printf("FD %d is closed\n", fd);
    }

    return 0;
}
