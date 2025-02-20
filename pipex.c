#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc == 5)
	{
		int infile = open (argv[1], O_RDONLY);
		if (infile == -1)
			exit (1);
		int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			exit (1);
		int fd[2];
		if (pipe(fd) == -1)
			exit (-1);
		int id1 = fork();
		if (id1 == 0)
		{
			dup2(infile, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(infile);
			close(fd[1]);
			char **args = ft_split(argv[2], ' ');
			char *cmd1 = ft_strdup(args[0]);
			char *bath = ft_strjoin("/bin/", cmd1);
			execve(bath, args, NULL);
			perror("execve 1 failed");
			exit(1);
		}
		int id2 = fork();
		if (id2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(fd[1]);
			close(outfile);
			close(fd[0]);
			char **args = ft_split(argv[3], ' ');
			char *cmd2 = ft_strdup(args[0]);
			char *bath = ft_strjoin("/bin/", cmd2);
			execve(bath, args, NULL);
			perror("execve 2 failed");
			exit(1);
		}
		close(fd[1]);
		close(fd[0]);
		waitpid(id1, NULL, 0);
		waitpid(id2, NULL, 0);
	}
	else
	{
		ft_printf(RED"(ERROR) ARGS SHOULD BE 5 ONLY\n"RESET);
		ft_printf(RED"(EXPECTED) ./pipex file1 cmd1 cmd2 file2\n"RESET);
	}
}