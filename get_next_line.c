/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:31:33 by bminner           #+#    #+#             */
/*   Updated: 2019/11/14 15:17:21 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_free(char **cache, int r)
{
	if (*cache)
	{
		free(*cache);
		*cache = 0;
	}
	return (r);
}

char		*ft_malloc(void)
{
	char *dest;

	if (!(dest = (char*)malloc(sizeof(char))))
		return (0);
	dest[0] = '\0';
	return (dest);
}

int			find_end_string(char *cache)
{
	int n;

	n = 0;
	while (cache[n] != '\0')
	{
		if (cache[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

int			place_line(char **line, char **cache, int n)
{
	char	*temp;
	int		r;

	if (n >= 0)
	{
		if (!(*line = ft_substr(*cache, 0, n)))
			return (ft_free(cache, -1));
		if (!(temp = ft_substr(*cache, n + 1, ft_strlen(*cache) - n)))
			return (ft_free(cache, -1));
		r = 1;
	}
	else
	{
		if (!(*line = ft_substr(*cache, 0, ft_strlen(*cache))))
			return (ft_free(cache, -1));
		temp = 0;
		r = 0;
	}
	ft_free(cache, 0);
	*cache = temp;
	return (r);
}

int			get_next_line(int fd, char **line)
{
	ssize_t			n;
	char			buff[BUFFER_SIZE + 1];
	static char		*cache;
	char			*temp;

	if(fd < 0 || !line)
		return (-1);
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		if (!(temp = ft_strjoin(cache, buff)))
			return (ft_free(&cache, -1));
		ft_free(&cache, 0);
		cache = temp;
		if (find_end_string(cache) >= 0)
			break ;
	}
	if (n < 0)
		return (ft_free(&cache, -1));
	if (n == 0 && (!cache || *cache == '\0')
					&& (*line = ft_malloc()))
			return (ft_free(&cache, 0));
	return (place_line(line, &cache, find_end_string(cache)));
}

int    main(int argc, char **argv)
{
    int        i;
    int        fd;
    char    *line;
    int        ret;
    printf("limit fdmax %d\n", OPEN_MAX);
    if (argc != 2)
    {
        printf("You forgot the filename");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    i = 1;
    while ((ret = get_next_line(fd, &line)) == 1)
    {
        printf("%3d [%s]\n", i, line);
        free(line);
        i++;
    }
    printf("%3d [%s]\n", i, line);
    free(line);
    if (ret == -1)
        printf("error\n");
    else if (ret == 0)
        printf("EOF\n");
    close(fd);
    return (0);
}
