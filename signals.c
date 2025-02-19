#include "pipex.h"

void	handle_sig(int sig)
{
	printf("input number: ");
	fflush(stdout);
}

int main(void)
{
	struct sigaction sa;
	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_RESTART;
	//sigaction(SIGTSTP, &sa, NULL); // ctrl + z
	sigaction(SIGCONT, &sa, NULL);   // when typing fg command on terminal

	int x;
	printf("input number: ");
	scanf("%d", &x);
	printf("10 * %d = %d\n",x, x * 10);
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