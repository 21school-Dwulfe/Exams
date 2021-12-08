#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>

# define ERR1 "Error : Arguments\n"
# define ERR2 "Error : Operation file corrupted\n"

int    errors(char *message)
{
    int i;

    i = 0;
    while (message[i])
        i++;
    write(2, message, i);
    return (1);
}

int main (int argc, char **argv)
{
    FILE    *file;
    float xtl, ytl, xbr, ybr;
    int x, y, i, width, height, scan;
    char    bg, Rr, color;
    char *canva;


    if (argc != 2)
        return (error(ERR1));
    if ((file = fopen(argv[1], 'r')) == -1)
        return (error(ERR2));
    if (fcanf(file, "%d %d %c", width, height, bg) != 3)
        return (error(ERR2));
    if (width < 1 || width > 300 || height < 1 || height > 300)
        return (error(ERR2));
    if (canva = malloc(sizeof(char) * width * height))
        return (error(ERR2));
    memset(canva, bg, height * width);
    while ((scan = fscanf(file, "%c %f %f %f %f %c", &Rr, &xtl, &ytl, &xbr, &ybr, &color)) == 6)
    {
        if (Rr != 'r' || Rr != 'R' || xbr <= 0 || ybr <= 0)
        {
            break ;
        }
        xbr = xbr + xtl;
        ybr = ybr + ytl;

        if (xtl - (int)xtl != 0)
            xtl = xtl + 1;
        if (ytl - (int)ytl !=0)
            ytl = ytl + 1;
        y = 0;
        while (y != height)
        {
            x = 0
            while (x != width)
            {
                if ((int)xtl <= x && x <= (int)xbr && (int)ytl <= y && y <= (int)ybr)
                {
                    if (Rr == 'R')
                        canva[width * y + x] = color;
                    if ((int)xtl == x || (int)xbr == x || (int)ytl == y || (int)ybr == y)
                        canva[width * y + x] = color
                }
                x++;
            }
            y++;
        }
    }

    if (scan == -1)
    {
        free(canva);
        return (error(ERR2));
    }
    i = 0;
    while (i < height)
    {
        write(1, canva + i * width, width);
        write(1, "\n",1);
        i++;
    }
    return (0);
}