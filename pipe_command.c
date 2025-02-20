#include "pipex.h"

int main(void)
{
	int fd[2];
	pipe(fd);

	int id1 = fork();
	if (id1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}

	int id2 = fork(); // the first child got replaced by the ping program

	if (id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execlp("grep", "grep", "rtt", NULL);
	}
	
	close(fd[1]);
	close(fd[0]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}