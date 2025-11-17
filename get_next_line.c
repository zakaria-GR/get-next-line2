#include "get_next_line.h"

char	*free_and_return_null(char *ptr1, char *ptr2)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free (ptr2);
	return (NULL);
}

char	*read_to_stash(int fd, char *stash)
{
	char	*buff;
	ssize_t	nb_read;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free_and_return_null(stash, NULL));
	while (!findnline(stash))
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == 0)
			break ;
		if (nb_read < 0)
			return (free_and_return_null(buff, stash));
		buff[nb_read] = '\0';
		temp = ft_strjoin(stash, buff);
		if (!temp)
			return (free_and_return_null(buff, stash));
		free (stash);
		stash = temp;
	}
	free (buff);
	return (stash);
}

char	*extract_line_and_update_stash(char **stash)
{
	int		y;
	char	*line;
	char	*leftover;
	int		i;

	y = countToNewLine(*stash);
	line = ft_substr(*stash, 0, y + 1);
	if (!line)
	{
		free (*stash);
		*stash = NULL;
		return (NULL);
	}
	i = ft_strlen(*stash);
	leftover = ft_substr(*stash, y + 1, i - (y + 1));
	if (!leftover)
	{
		free (line);
		free (*stash);
		*stash = NULL;
		return (NULL);
	}
	free (*stash);
	*stash = leftover;
	return (line);
}

char	*extract_final_line(char **stash)
{
	int		i;
	char	*line;

	i = ft_strlen(*stash);
	line = ft_substr(*stash, 0, i);
	if (!line)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	free (*stash);
	*stash = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_to_stash(fd, stash);
	if (stash != NULL)
	{
		if (findnline(stash))
			return (extract_line_and_update_stash(&stash));
		else if (stash[0] != '\0')
			return (extract_final_line(&stash));
		free(stash);
		stash = NULL;
		return (NULL);
	}
	free (stash);
	return (NULL);
}
