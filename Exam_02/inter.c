#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	char bit[255];

	if (argc == 3)
	{
		i = 0;
		while (i < 255)
			bit[i++] = 0;
		i = 0;
		while (argv[2][i])
		{
			bit[(unsigned int)argv[2][i]]++;
			i++;
		}
		i = 0;
		while (argv[1][i])
		{
			if (bit[(unsigned int)argv[1][i]]++ == 1)
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1 , "\n", 1);
	return (0);
}