#include "pipex.h"

int	open_f(char *file, int r_or_w)
{
	int	fd;

	if (r_or_w == 0)
		fd = open(file, O_RDONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		exit(-1);
	return (fd);
}
