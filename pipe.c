#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i = 0;
	int j = 0;
	long long s_big = 0; // parent 
	long long s = 0; // child
	long long final = 0;
	char sum_new[20];
	int pipe_fd[2];
	if (pipe(pipe_fd) < 0){
		printf("pipe failed\n");
		exit(1);
	}
	
	pid_t p = fork();
	if (p < 0) {
		printf("fprk failed\n");
		exit(1);
	}

	if (p == 0) {
		close(pipe_fd[0]);
		for (i = 0; i < 1000000000; i++)
			s = s + i;
		sprintf (sum_new, "%lld", s);
		write (pipe_fd[1], sum_new, 20);
		close(pipe_fd[1]);
		exit(0);
	}
	else {
		for (j = 1000000000; j < 2000000001; j++)
			s_big = s_big + j;
		read (pipe_fd[0], sum_new, 20);
		long long sum_new_converted = atoll(sum_new);
		final = s_big + sum_new_converted;
		printf ("%lld is the sum\n", final);
		close(pipe_fd[1]);

	}
	waitpid (-1, 0, 0);
	return 0;


}
