# include "pipex.h"
// fd[0] reading / fd[1] writing
int main(void)
{
	int p1[2]; 
	pipe(p1);
	int id = fork();

	if(id == 0)
	{
		close(p1[0]);
		int err = execlp("ping", "ping", "-c", "2", "google.con", NULL);
		if (err == -1)
		{
			write(p1[1], &err, sizeof(int));
			printf("could not find program\n");
			close(p1[1]);
		}
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		close(p1[1]);
		int er;
		read(p1[0], &er, sizeof(int));
		close(p1[0]);
		if (er == -1)
		{
			printf("program failed\n");
			return (1);
		}
		if(WIFEXITED(wstatus)) //Returns true if the child process exited normally (not due to a signal).
		{
			int statusCode = WEXITSTATUS(wstatus); //Extracts the exit status of the child process if it exited normally
			if (statusCode == 0)
				printf("success statusCode: %d!!\n", statusCode);
			else
				printf("failure with statusCode: %d!!\n", statusCode);
		}
		
	}
}

/*
{
	int p1[2]; // C => P
	int p2[2]; // P => C
	
	pipe(p1);
	pipe(p2);

	int id = fork();
	if (id == 0)
	{
		close(p1[0]);
		close(p2[1]);
		int x;
		read(p2[0], &x, sizeof(int));
		printf("recieved: %d\n", x);
		x += 3;
		write(p1[1], &x, sizeof(int));
		printf("sent: %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}
	else
	{
		close(p1[1]);
		close(p2[0]);
		int x = 42;
		write(p2[1], &x, sizeof(int));
		printf("sent to child: %d\n", x);
		read(p1[0], &x, sizeof(int));
		printf("recived from child: %d\n", x);
		close(p1[0]);
		close(p2[1]);
		wait(NULL);
	}
}
*/
/*
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
*/