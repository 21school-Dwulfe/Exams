#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Err1 "Error: argument"
#define Err2 "Error: Operation file corrupted"

int error(char *mes)
{
    int i = 0;
    while (mes[i])
        i++;
    write(1, mes, i);
    return (1);
}

int main(int argc, char **argv)
{
    char bg, Cc, color;
    int width, height, i, scan;
    float xb, yb, radius, dist;
    int xa, ya;
    FILE *file;
    char *canva;

    file = NULL;
    if (argc != 2)
        return (error(Err1));
    if ((file = fopen(argv[1], "r")) == NULL)
        return (error(Err2));
    if (fscanf(file, "%d %d %c\n", &width, &height, &bg) != 3)
        return (error(Err2));
    if (width < 1 || width > 300 || height < 1 || height > 300)
        return (error(Err2));
    if ((canva = malloc(sizeof(char) * height * width)) == NULL)
        return (error(Err2));
    memset(canva, bg, sizeof(char) * width * height);

    while ((scan = fscanf(file, "%c %f %f %f %c\n", &Cc, &xb, &yb, &radius, &color)) == 5)
    {
        if (radius <= 0 || (Cc != 'c' && Cc != 'C'))
            break ;
        ya = 0;
        while (ya < height)
        {
            xa = 0;
            while (xa < width)
            {
                dist = sqrtf(((float)xa - xb) * ((float)xa - xb) + ((float)ya - yb)* ((float)ya - yb));
                if (dist <= radius)
                {
                    if ( dist + 1 > radius && Cc == 'c')//radius - dist < 1.000000
                        canva[width * ya + xa] = color;
                    if (Cc == 'C')
                        canva[width * ya + xa] = color;
                }
                xa++;
            }
            ya++;
        }
    }

    if (scan != -1)
    {
        free(canva);
        return(error(Err2));
    }
        i = 0;
    while (i < height)
    {
        write(1, canva + width * i, width);
        write(1, "\n", 1);
        i++;
    }
    return (0);
}