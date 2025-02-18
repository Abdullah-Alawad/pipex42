# include "pipex.h"

int	main(int argc, char **argv)
{
	int	num[] = {4, 1, 3 ,6 ,7, 6, 4, 3, 5};
	int	numSize = sizeof(num) / sizeof(int);
	int start, end;
	int	fd[2];
	pipe(fd);
	int id1 = fork();
	int id2;
	if (id1 != 0)
		id2 = fork();
	if (id1 == 0)
	{
		start = 0;
		end = numSize / 3;
	}
	else if (id2 == 0)
	{
		start = numSize / 3;
		end = numSize - (numSize / 3);
	}
	else
	{
		start = numSize - (numSize / 3);
		end = numSize;
	}

	int i = start;
	int sum = 0;
	while(i < end)
		sum += num[i++];
	printf("partial sum is %d\n", sum);
	if (id1 == 0 || id2 == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int s1, s2;
		read(fd[0], &s1, sizeof(int));
		read(fd[0], &s2, sizeof(int));
		close(fd[0]);
		int total = s1 + s2 + sum;
		printf("total sum: %d\n", total);
		wait(NULL);
	}

}