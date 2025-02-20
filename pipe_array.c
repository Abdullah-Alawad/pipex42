#include "pipex.h"

// create 2 processes
// generate array of ints in one process
// sent the array to the other process and print their sum

int main(void)
{
	int fd[2];
	pipe(fd);

	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int arr[10];
		int n, i;

		srand(time(NULL));
		n = rand() % 10;
		printf("arr size: %d\n", n);
		printf("generated: ");
		i = 0;
		while (i < n)
		{
			arr[i] = rand() % 11; // 0 to 10 numbers
			printf("%d ", arr[i]);
			i++;
		}
		printf("\n");
		write(fd[1], &n, sizeof(int));
		write(fd[1], arr, sizeof(int) * n);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int arr[10];
		int n, i, sum;
		read(fd[0], &n, sizeof(int));
		printf("recieved arr size: %d\n", n);
		read(fd[0], arr, sizeof(int) * n);
		i = 0;
		sum = 0;
		while(i < n)
		{
			sum += arr[i];
			i++;
		}
		printf("sum is %d\n", sum);
		wait(NULL);
	}
}