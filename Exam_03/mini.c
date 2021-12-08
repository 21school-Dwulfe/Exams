#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

# define ERR1 "Error: argument\n"
# define ERR2 "Error: Operation file corrupted\n"

int error(char *err)
{
	int i = 0;
	while (err[i] != '\0')
		i++;
	write(1, err, i);
	return (1);
}


int main(int ac, char **av)
{
	FILE *file;

	int wcanv, hcanv;
	char bg;

	char *canvas;

	int scan, xa, ya;

	char Cc;
	float xb, yb, radius;
	char color;

	float dist;

	int i = 0;
	if (ac != 2)
		return (error(ERR1));
	else if(!(file = fopen(av[1], "r")))
		return (error(ERR2));
	else if ((fscanf(file, "%d %d %c\n", &wcanv, &hcanv, &bg)) != 3)
		return (error(ERR2));
	else if ((!(0 < wcanv && wcanv <= 300)) || (!(0 < hcanv && hcanv <= 300)))
		return (error(ERR2));
	else if ((!(canvas = (char *)malloc(sizeof(char) * wcanv * hcanv))))
		return (error(ERR2));
	else
		memset(canvas, bg, wcanv * hcanv);
	while ((scan = fscanf(file, "%c %f %f %f %c\n", &Cc, &xb, &yb, &radius,
						  &color)) == 5)
	{
		if (radius <= 0 || (Cc != 'c' && Cc != 'C'))
			break;
		ya = 0;
		while (ya != hcanv)
		{
			xa = 0;
			while (xa != wcanv)
			{
				dist = sqrtf(((float)xa - xb) * ((float)xa - xb) +
							 ((float)ya - yb) * ((float)ya - yb));
				if (dist <= radius)
				{
					if (radius - dist < 1.00000000 && Cc == 'c')
						canvas[ya * wcanv + xa] = color;
					if (Cc == 'C')
						canvas[ya * wcanv + xa] = color;
				}
				xa++;
			}
			ya++;
		}

	}
	if (scan != -1)
	{
		free(canvas);
		return(error(ERR2));
	}
	while (i != hcanv)
	{
		write(1, canvas + i * wcanv, wcanv);
		write(1, "\n", 1);
		i++;
	}
	free(canvas);
	fclose(file);
	return(0);
}