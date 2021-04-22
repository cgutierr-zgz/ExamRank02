/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgutierr <cgutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:29:20 by cgutierr          #+#    #+#             */
/*   Updated: 2021/04/22 22:11:41 by cgutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

typedef struct s_printf
{
	int width;
	int precission;
	int len;
	int i;
	int n;
	va_list ap;
} t_printf;

char *ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (char *)str;
		str++;
	}

	if (*str == c)
		return (char *)str;
	return NULL;
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;

	return i;
}

void print_spaces(t_printf *pstruct, int n, char zero)
{
	int i = 0;
	while (i < n)
	{
		pstruct->n += write(1, &zero, 1);
		i++;
	}
}

void printstr(t_printf *pstruct, char *str)
{
	int len = 0;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (pstruct->precission == 0)
		len = 0;
	if (pstruct->precission > 0 && pstruct->precission < len)
		len = pstruct->precission;
	if (pstruct->width > len)
		print_spaces(pstruct, pstruct->width - len, ' ');
	pstruct->n += write(1, str, len);
}

void lennum(long long int n, char *base, int *len)
{
	int b = ft_strlen(base);
	if (n >= b)
		lennum(n / b, base, len);
	*len = *len + 1;
}
void putnbr(t_printf *pstruct, long long int n, char *base)
{
	int b = ft_strlen(base);
	if (n >= b)
		putnbr(pstruct, n / b, base);
	pstruct->n += write(1, &base[n % b], 1);
}

void printnum(t_printf *pstruct, int n)
{

	int len;
	int final = 0;
	int neg = 0;

	len = 0;
	if (n == 0 && pstruct->precission == 0)
		len = -1;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
		pstruct->width--;
	}
	lennum(n, "0123456789", &len);
	if (pstruct->width > pstruct->precission && pstruct->width > len)
	{
		if (pstruct->precission > len)
			print_spaces(pstruct, pstruct->width - pstruct->precission, ' ');
		else
			print_spaces(pstruct, pstruct->width - len, ' ');
	}
	if (neg == 1)
		pstruct->n += write(1, "-", 1);
	if (pstruct->precission > len)
		print_spaces(pstruct, pstruct->precission - len, '0');
	if (!(n == 0 && pstruct->precission == 0))
		putnbr(pstruct, n, "0123456789");
}

void printhexa(t_printf *pstruct, unsigned int n)
{
	int len;
	int final = 0;

	len = 0;
	if (n == 0 && pstruct->precission == 0)
		len = -1;
	lennum(n, "0123456789abcdef", &len);
	if (pstruct->width > pstruct->precission && pstruct->width > len)
	{
		if (pstruct->precission > len)
			print_spaces(pstruct, pstruct->width - pstruct->precission, ' ');
		else
			print_spaces(pstruct, pstruct->width - len, ' ');
	}
	if (pstruct->precission > len)
		print_spaces(pstruct, pstruct->precission - len, '0');
	if (!(n == 0 && pstruct->precission == 0))
		putnbr(pstruct, n, "0123456789abcdef");
}

int ft_printf(const char *fmt, ...)
{
	t_printf pstruct;
	pstruct.i = 0;
	pstruct.len = 0;
	pstruct.precission = -1;
	pstruct.width = 0;
	pstruct.n = 0;
	va_start(pstruct.ap, fmt);

	while (fmt[pstruct.i])
	{
		pstruct.width = 0;
		pstruct.precission = -1;
		if (fmt[pstruct.i] != '%')
			pstruct.n += write(1, &fmt[pstruct.i], 1);
		else
		{
			pstruct.i++;
			while (ft_strchr("0123456789", fmt[pstruct.i]))
			{
				pstruct.width = pstruct.width * 10 + (fmt[pstruct.i] - '0');
				pstruct.i++;
			}
			if (fmt[pstruct.i] == '.')
			{
				pstruct.i++;
				pstruct.precission = 0;
				while (ft_strchr("0123456789", fmt[pstruct.i]))
				{
					pstruct.precission = pstruct.precission * 10 + (fmt[pstruct.i] - '0');
					pstruct.i++;
				}
			}
			if (ft_strchr("sdx", fmt[pstruct.i]))
			{
				if (fmt[pstruct.i] == 's')
					printstr(&pstruct, va_arg(pstruct.ap, char *));
				if (fmt[pstruct.i] == 'd')
					printnum(&pstruct, va_arg(pstruct.ap, int));
				if (fmt[pstruct.i] == 'x')
					printhexa(&pstruct, va_arg(pstruct.ap, unsigned int));
			}
			else
				break;
		}

		pstruct.i++;
	}
	va_end(pstruct.ap);
	return pstruct.n;
}
#include <stdio.h>
int main()
{
	int a, b;
	a = ft_printf("[sapatito%12s %15d]\n", "sopete", 155);
	b = printf("[sapatito%12s %15d]\n", "sopete", 155);
	printf("ft=%d|printf=%d\n\n", a, b);

	a = ft_printf("[%12.5x]\n", 321313231);
	b = printf("[%12.5x]\n", 321313231);
	printf("ft=%d|printf=%d\n\n", a, b);
}