# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <string.h>

# define CD_BAD_ARG "error: cd: bad arguments"
# define CD_CANNOT_EXEC "error: cd: cannot change directory to"
# define ERROR_FATAL "error: fatal"
# define ERROR_EXECVE "error: cannot execute "

int	error(char *error, char *arg)
{
	int i;

	i = 0;
	while (error[i])
		i++;
	if (write(2, error, i) == -1)
		exit(1);
	if (arg)
	{
		i = 0;
		while (arg[i])
			i++;
		if (write(2, arg, i) == -1)
			exit(1);
	}
	if (write(2, "\n", 1) == -1)
			exit(1);
	return (1);
}

void	micro_close(int fd)
{
	if (close(fd) == -1)
		error(ERROR_FATAL, NULL);
}
void	micro_dup2(int fd, int new)
{
	if (dup2(fd, new) == -1)
		error(ERROR_FATAL, NULL);
}

int	cd_exec(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (error(CD_BAD_ARG, NULL));
	else
	{
		if (chdir(args[1]) == -1)
			return (error(CD_CANNOT_EXEC, args[1]));
	}
	return (2);
}

int	 main(int argc, char **argv, char **env)
{
	int		i;
	int 	j;
	int		stat;
	pid_t	pid;
	int		piped;
	int		opened_pipe;
	int		fd_pipe[2];
	int		fd_s[2];
	int 	num_args;
	char 	**cmd;

	if (argc < 2)
		return (0);
	argv++;
	stat = 0;
	i = 0;
	fd_s[0] = dup(0);
	fd_s[1] = dup(1);
	cmd = NULL;
	if (fd_s[0] == -1 || fd_s[1] == -1)
		error(ERROR_FATAL, NULL);
	i = 0;
	while (argv[i])
		i++;
	i = 0;
	while (argv && argv[i])
	{
		while (argv[i] && (!strncmp(argv[i], "|", 2) || !strncmp(argv[i], ";", 2)))
		{
			i++;
			continue ;
		}
		num_args = 0;
		while (argv[i + num_args] && strncmp(argv[i + num_args], "|", 2) && strncmp(argv[i + num_args], ";", 2))
			num_args++;
		if (argv[i + num_args] && !strncmp(argv[i + num_args], "|", 2))
			piped = 1;
		else
			piped = 0;
		if (i - 1 > -1 && !strncmp(argv[i - 1], "|", i))
			opened_pipe = 1;
		else
			opened_pipe = 0;
		if (cmd)
		{
			free(cmd);
			cmd = NULL;
		}
		if ((cmd = malloc(sizeof(char *) * (num_args + 1))) == NULL)
			return(error(ERROR_FATAL, NULL));
		j = 0;
		while (j < num_args)
		{
			cmd[j] = argv[i + j];
			j++;
		}
		cmd[j] = NULL;
		i += j;
		if (cmd && num_args && !strncmp(cmd[0], "cd", 3))
			stat = cd_exec(cmd);
		if (!stat)
		{
			if (opened_pipe)
			{
				micro_dup2(fd_pipe[0], 0);
				micro_close(fd_pipe[0]);
				fd_pipe[0] = 0;
			}
			if (piped)
			{
				if (pipe(fd_pipe) == -1)
					error(ERROR_FATAL, NULL);
				micro_dup2(fd_pipe[1], 1);
				micro_close(fd_pipe[1]);
				fd_pipe[1] = 0;
			}
			pid = fork();
			if (pid == 0)
			{
				micro_close(fd_s[0]);
				micro_close(fd_s[1]);
				// if (!piped)// && opened_pipe
				// 	micro_close(fd_pipe[1]);
				// if (piped)
				// 	micro_close(fd_pipe[0]);
				if (cmd && cmd[0] && execve(cmd[0], cmd, env) == -1)
					error(ERROR_EXECVE, cmd[0]);
				free(cmd);
				exit(1);
			}
		}
		micro_dup2(fd_s[1], 1);
	}
	micro_dup2(fd_s[0], 0);
	micro_dup2(fd_s[1], 1);
	micro_close(fd_s[0]);
	micro_close(fd_s[1]);
	waitpid(0, &stat, 0);
//	while (1){}
	return (stat);
}