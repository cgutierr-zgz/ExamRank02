/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgutierr <cgutierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:33:14 by cgutierr          #+#    #+#             */
/*   Updated: 2021/04/22 22:11:38 by cgutierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int get_next_line(char **line)
{
	int n_bytes;
	int i;
	char buff;
	char *copy;

	if (!((*line) = malloc(1)))
		return -1;
	(*line)[0] = '\0';
	while ((n_bytes = read(0, &buff, 1)) > 0)
	{
		if (buff == '\n' || buff == '\0')
			break;
		i = 0;
		while ((*line)[i])
		{
			i++;
		}

		if (!(copy = malloc(i + 2)))
			return -1;
		i = 0;
		while ((*line)[i])
		{
			copy[i] = (*line)[i];
			i++;
		}
		copy[i++] = buff;
		copy[i++] = '\0';
		free(*line);
		*line = copy;
	}
	return n_bytes;
}