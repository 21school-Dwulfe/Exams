#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int g_length;
int g_w;
int g_ac;

char	*ft_atoi_base(unsigned int num, int base)
{
	int i;
	unsigned int tmp;
	char *result;

	tmp = num;
	i = 0;
	if (num == 0)
		i++;
	while (tmp)
	{
		tmp /= base;
		i++;
	}
	result = malloc(sizeof(char) * (i + 1));
	while (i)
	{
		tmp = num % base;
		if (tmp > 9)
			result[i - 1] = tmp + 'a' - 10;
		else
			result[i - 1] = tmp + '0';
		num /= base;
		i--;
	}
	return(result);
}


void	ft_print_d(int num)
{
	char	minus;
	int		i;
	int		len;
	char	*str;
	
	i = 0;
	len = 0;
	minus = 0;
	str = ft_atoi_base(num, 16);
	if (num < 0)
	{
		minus = 1;
		g_w--;
	}
	while (str[i])
	{i++; len++;}
	if (g_ac != -1 && g_ac > i)
		i = g_ac;
	while (g_w > i)
	{
		g_length += write(1, " ", 1);
		g_w--;
	}
	if (minus == 1)
		g_length += write(1, "-", 1);
	while (i > len)
	{
		g_length += write(1, "0", 1);
		i--;
	}
	g_length += write(1, str, len);
	free(str);
}

void	ft_print_x(unsigned int num)
{
	int i;
	int len;
	char *str;
	
	i = 0;
	len = 0;
	str = ft_atoi_base(num, 16);
	while (str[i])
	{ i++; len++;}
	if (g_ac != -1 && g_ac > i)
		i = g_ac;
	while (g_w > i)
	{
		g_length += write(1, " ", 1);
		g_w--;
	}
	while (i > len)
	{
		g_length += write(1, "0", 1);
		i--;
	}
	g_length += write(1, str, len);
	free(str);
}

void	ft_print_s(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	if (g_ac != -1 && g_ac < i)
		i = g_ac;
	while (g_w > i)
	{
		g_length += write(1, " ", 1);
		g_w--;
	}
	g_length += write(1, str, i);
}

int	ft_printf(char *str, ...)
{
	int i;
	va_list args;

	i = 0;
	g_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			printf("write %%");
			i++;
			g_w = 0;
			g_ac = -1;
			while (str[i] >= '0' && '9' <= str[i])
				g_w = g_w * 10 + (str[i++] - '0');
			if (str[i] == '.')
			{
				i++;
				g_ac = 0;
				while (str[i] >= '0' && '9' <= str[i])
					g_ac = g_ac * 10 + (str[i++] - '0');
			}
			if (str[i] == 's')
				ft_print_s(va_arg(args, char *));
			else if (str[i] == 'x')
				ft_print_x(va_arg(args, unsigned int));
			else if (str[i] == 'd')
				ft_print_d(va_arg(args, int));
			else
				g_length += write(1, &str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (g_length);
}

int main(void)
{
 ft_printf("%s", "yahoo");
	//printf("orig len = %d\n", printf("%s", "yahoo"));
//ft_printf("orig len = %d\n",
	 ft_printf("%10.8x\n", 42);
	//printf("orig len = %d\n", printf("%10.8x\n", -42));

	//ft_printf("%10.8d\n", -42);
	//printf("%10.8d\n", -42);
	return (0);
}