#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int generate_natural();  
int prime_filter(int in_fd, int prime); 

int main(int argc, char *argv[])
{
	int prime; 
	
	int in_fd = generate_natural();
	while (1) {
        if (read(in_fd, &prime, sizeof(int)) == 0) break;  
        printf("prime %d\n", prime);
        in_fd = prime_filter(in_fd, prime);
    }

	exit(0);
}


int generate_natural() {
	int fd[2];
	
	pipe(fd);

    int id = fork();

	if (id == 0) {
		for (int i = 2; i <= 280; i++) {
			write(fd[1], &i, sizeof(int));
		}
		close(fd[1]);

		exit(0);
	}

	close(fd[1]);

	return fd[0];
}

int prime_filter(int in_fd, int prime) 
{
	int num;
	int fd[2];

	pipe(fd);

    int id = fork();

	if (id == 0) {
		 while (1) {
            if (read(in_fd, &num, sizeof(int)) == 0) break;
            if (num % prime != 0) {
                write(fd[1], &num, sizeof(int));
            }
        }
		close(in_fd);
		close(fd[1]);
		
		exit(0);
	}

	close(in_fd);
	close(fd[1]);

	return fd[0];
}