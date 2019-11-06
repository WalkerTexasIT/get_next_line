/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:31:07 by bminner           #+#    #+#             */
/*   Updated: 2019/10/31 12:31:08 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t		find_end_string(char temp, ssize_t n)
{
	while (n != 0)
	{
		
	}
	return (n);
}


int		get_next_line(int fd, char **line)
{
	ssize_t		n;
	ssize_t		i;
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	char		*cache;

	if (fd < 0 || !line)
		return (-1);
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		temp = buff;
		i = find_end_string(temp, n);
		if (i > 0)
			if (!(place_string(temp, cache)))
				return (ft_free(&cache, -1));
		if (i > 0)
			break ;
	}
	if (n < 0)
		return (-1);
}