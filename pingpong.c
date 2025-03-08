#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main() {
    int fd[2];
    pipe(fd);
    char buf = 'A';

    if(fork() == 0) {
        read(fd[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(fd[1], &buf, 1);
        exit(0);
    }
    else {
        write(fd[1], &buf, 1);
        wait(0);
        read(fd[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}