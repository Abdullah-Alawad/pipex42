#include "pipex.h"

int main(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	int fd = open("sum", O_WRONLY);

	write(fd, arr, sizeof(int) * 5);
	close(fd);
	fd = open("sum", O_RDONLY);
	int sum;
	read(fd, &sum, sizeof(int));
	close(fd);
	printf("sum recieved: %d\n", sum);
}