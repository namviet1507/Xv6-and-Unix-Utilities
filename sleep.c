#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Use: sleep + [time]\n");
        exit(1);
    }

    int time = atoi(argv[1]);
    if(time <= 0) {
        printf("Invalid value\n");
        exit(1);
    }
    sleep(time);

    exit(0);
}