# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

int ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_cd_bad_args(void)
{
	write(2 , "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
}

void ft_cd_cant_change_dir(char *str)
{
	write(2 , "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(2 , str, ft_strlen(str));
	write(2 , "\n", 1);
}

void ft_fatal(void)
{
	write(2 , "error: fatal\n", ft_strlen("error: fatal\n"));
}

void ft_cant_execute(char *str)
{
	write(2 , "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(2 , str, ft_strlen(str));
	write(2 , "\n", 1);
}

void ft_cd(char **line)
{
	int i = 0;
	while (line[i])
	{
		i++;
	}
	if (i != 2)
	{
		ft_cd_bad_args();
		return;
	}
	else
		if(chdir(line[1]))
			ft_cd_cant_change_dir(line[1]);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;
	int len;
	int j;
	char **line;
	int f_cd = 0;
	int f_pipe = 0;
	int opend = 0;
	int fds[2];
	int fd[2];
	pid_t pid;
	int status = 0;
		
	while(argc > 1 && i < argc)
	{
		if ((!strcmp(argv[i], ";") || !strcmp(argv[i], "|")))
		{
			i++;
			continue;
		}
		len = 0;
		while(argv[i + len] && strcmp(argv[i + len], ";") && strcmp(argv[i + len], "|"))
			len++;
		if (!(line = (char **)malloc(sizeof(char*) * (len + 1 ))))
			ft_fatal ();
		line[len] = NULL;
		j = 0;
		
		while (j < len)
		{
			line[j] = argv[i];
			// printf("%s\n", line[j]);
			if (!strcmp(argv[i], "cd"))
				f_cd = 1;
			// printf("%d\n", f_cd); 
			j++;
			i++;
		}
		if (argv[i] && !strcmp(argv[i], "|"))
			f_pipe = 1;
		else
			f_pipe = 0;
		// printf("pipe %d\n", f_pipe);
		// printf("количество команд %d\n", len);
		if ((argv[i] && !strcmp(argv[i], "cd")) || f_cd)
			ft_cd(line);
		
		if (opend)
		{
			fds[0] = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		
		if (f_pipe)
		{   
			if (pipe(fd))
				ft_fatal();
			fds[1] = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		pid = fork();
		if (pid < 0)
			ft_fatal();
		else if (!pid)
		{
			if (!f_cd)
			{
				if (execve(line[0], line, env))
					ft_cant_execute(line[0]);
			}
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
		if (opend)
		{
			dup2(fds[0], 0);
			close(fds[0]);
			opend = 0;
		}
		if (f_pipe)
		{         
			dup2(fds[1], 1);
			close(fds[1]);
			opend = 1;
		}
		f_cd = 0;
		free(line);

	}
		
	return (0);
}

//"error: cd: bad arguments" 
//"error: cd: cannot change directory to path_to_change" 
//"error: fatal"
//"error: cannot execute executable_that_failed"

