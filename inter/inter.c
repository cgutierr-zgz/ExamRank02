/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgutierr <cgutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:33:20 by cgutierr          #+#    #+#             */
/*   Updated: 2021/04/22 22:11:34 by cgutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

int main(int argc, char **argv)
{
	int a, b, c;
	a = 0;
	b = 0;
	c = 0;
	char sapato[255];
	if (argc == 3)
	{
		while (argv[1][a])
		{
			b = 0;
			while (argv[2][b])
			{
				if (argv[1][a] == argv[2][b] && !ft_strchr(sapato, argv[1][a]))
				{
					write(1, &argv[1][a], 1);
					sapato[c] = argv[1][a];
					c++;
				}
				b++;
			}

			a++;
		}
	}
	write(1, "\n", 1);
}