#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# define ERR1 "Error : Arguments\n"
# define ERR2 "Error : Operation file corrupted\n"

int    error(char *message)
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
    int x, y, i, width = 0,
    height = 0,
    scan = 0;
    char  bg, Rr, color;
    char *canva;


    if (argc != 2)
        return (error(ERR1));
    if ((file = fopen(argv[1], "r")) == NULL)
        return (error(ERR2));
    if (fscanf(file, "%d %d %c\n", &width, &height, &bg) != 3)
        return (error(ERR2));
    if (width < 1 || width > 300 || height < 1 || height > 300)
        return (error(ERR2));
    if ((canva = malloc(sizeof(char) * width * height)) == NULL)
        return (error(ERR2));
    memset(canva, bg, height * width); 
   
    while ((scan = fscanf(file, "%c %f %f %f %f %c\n", &Rr, &xtl, &ytl, &xbr, &ybr, &color)) == 6)
    { 
        printf("%c %f %f %f %f %c\n", Rr, xtl, ytl, xbr, ybr, color);
        if ((Rr != 'r' && Rr != 'R' ) || xbr <= 0 || ybr <= 0)
            return (error(ERR2));
        xbr = xbr + xtl;
        ybr = ybr + ytl;

        if (xtl - (int)xtl != 0)
            xtl = xtl + 1;
        if (ytl - (int)ytl !=0)
            ytl = ytl + 1;
        y = 0;
       
        while (y != height)
        {  
            x = 0;
            while (x != width)
            { 
              
                if ((int)xtl <= x && x <= (int)xbr && (int)ytl <= y && y <= (int)ybr)
                { 
                   
                    if (Rr == 'R')
                       canva[width * y + x] = color;
                    if ((int)xtl == x || (int)xbr == x || (int)ytl == y || (int)ybr == y)
                    {
                        canva[width * y + x] = color;
                    }
                }
                x++;
            }
            y++;
        }
    }

    if (scan != -1)
    {
        printf("scan");
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
    free(canva);
    return (0);
}