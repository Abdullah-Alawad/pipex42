#include "pipex.h"

void	handle_sig(int sig)
{
	printf("(HINT) think harder:)\n");
}

int main(void)
{
	int pid = fork();

	if (pid == 0)
	{
		sleep(5);
		kill(getppid(), SIGUSR1);
	}
	else
	{
		struct sigaction sa;
		sa.sa_handler = &handle_sig;
		sa.sa_flags = SA_RESTART;
		//sigaction(SIGTSTP, &sa, NULL); // ctrl + z
		//sigaction(SIGCONT, &sa, NULL);   // when typing fg command on terminal
		sigaction(SIGUSR1, &sa, NULL);

		int x;
		printf("3 * 5 equals?... ");
		scanf("%d", &x);
		if (x == 15)
		{
			kill(pid, SIGKILL);
			printf("right!\n");
		}
		else
			printf("WRONG\n");
		wait(NULL);
	}
}

/*
{
	int pid = fork();

	if (pid == 0)
	{
		int i = 0;
		while (i >= 0)
		{
			printf("printing line %d\n", i);
			usleep(50000);
			i++;
		}
	}
	else
	{
		int t;
		kill(pid, SIGSTOP);
		do
		{
			printf("enter number of seconds ");
			scanf("%d", &t);

			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGSTOP);
			}
		} while (t > 0);
		kill(pid, SIGKILL);
		wait(NULL);
	}
}
*/