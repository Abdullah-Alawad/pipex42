#include "pipex.h"

int main(void)
{
    int arr[5];
    int fd = open("sum", O_RDONLY);

    read(fd, arr, sizeof(int) * 5);
    close(fd);
    int i = 0;
    int sum;
    while (i < 5)
    {
        sum += arr[i];
        printf("recieved: %d\n", arr[i]);
        i++;
    }
    printf("sum is: %d\n", sum);

    fd = open("sum", O_WRONLY | O_APPEND);
    write(fd, &sum, sizeof(int));
    close(fd);
}