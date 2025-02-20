#include "pipex.h"

int main(int argc, char **argv)
{
	int fd[2];
	pipe(fd);

	int id = fork();
	if (id == 0)
	{
		close(fd[0]);
		if (argc == 2)
		{
			int len = ft_strlen(argv[1]);
			printf("string len: %d\n", len);
			write(fd[1], &len, sizeof(int));
			write(fd[1], argv[1], len + 1);
		}
			close(fd[1]);
	}
	else
	{
		close(fd[1]);
		char *s;
		char c;
		int len, i;
		if (argc == 2)
		{
			read(fd[0], &len, sizeof(int));
			printf("received len: %d\n", len);
			s = malloc(len + 1);
			i = 0;
			while (i < len)
			{
				read(fd[0], &c, 1);
				s[i] = c;
				i++;
			}
			s[i] = '\0';
			printf("recieved string: %s\n", s);
			free(s);
		}
		close(fd[0]);
		wait(NULL);
	}
}