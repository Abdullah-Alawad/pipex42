#include "pipex.h"

int main(void)
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
			printf("\nenter number of seconds ");
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