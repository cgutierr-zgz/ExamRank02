/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgutierr <cgutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:33:20 by cgutierr          #+#    #+#             */
/*   Updated: 2021/04/22 22:11:32 by cgutierr         ###   ########.fr       */
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
	int a, b;
	a = 0;
	b = 0;
	char sapato[255];
	if (argc == 3)
	{
		while (argv[1][a])
		{
			if (!ft_strchr(sapato, argv[1][a]))
			{
				write(1, &argv[1][a], 1);
				sapato[b] = argv[1][a];
				b++;
			}

			a++;
		}
		a = 0;
		while (argv[2][a])
		{
			if (!ft_strchr(sapato, argv[2][a]))
			{
				write(1, &argv[2][a], 1);
				sapato[b] = argv[2][a];
				b++;
			}

			a++;
		}
	}
	write(1, "\n", 1);
}