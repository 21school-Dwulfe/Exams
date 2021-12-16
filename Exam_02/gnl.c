#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int gnl(char **line)
{
	char	ch;
	int		i;
	int		rd;
	char	*buffer;

	i = 0;
	rd = 0;
	buffer = malloc(100000);
	*line = buffer;
	while ((rd = read(1, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	if (rd == 0)
		free(buffer);
	return (rd);
}

int main(void)
{
	int rd = 0;
	char *line;

	line = NULL;
	while ((rd = gnl(&line)) > 0)
	{
		printf("%s\n",line);
		free(line);
		line = NULL;
	}
	return (0);
}