#include "get_next_line_bonus.h"

int	countToNewLine(char *str)
{
	int i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t		i;

	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		str = malloc(1);
		{
			if (!str)
				return NULL;
			str[0] = '\0';
			return (str);
		}
	}
	if (len > (s_len - start))
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return ((char *)str);
}

int	findnline(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return 1;
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	y = 0;
	while (i < (s1_len + s2_len))
		s3[i++] = s2[y++];
	s3[i] = '\0';
	return (s3);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	if (count != 0)
	{
		if (size > SIZE_MAX / count)
		{
			return (NULL);
		}
	}
	temp = (unsigned char *)malloc(count * size);
	if (!temp)
	{
		return (NULL);
	}
	while (i < (count * size))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}


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
	static	t_list	*stash;
	t_list			*temp;
	t_list			*new;
	t_list			*last;
	if (!stash)
	{
		stash = malloc(sizeof(t_list));
		if (!stash)
			return (NULL);
		stash->content = malloc(1);
		if(!stash->content)
		{
			free(stash);
			return (NULL);
		}	
		stash->content[0] = '\0';
		stash->next = NULL;
		stash->fd = fd;
	}
	temp = stash;
	while (temp)
	{
		printf("***");
		last = temp;
		if(temp->next == NULL && temp->fd != fd)
		{
			break ;
		}
		if (temp->fd == fd)  
		{
		temp->content = read_to_stash(fd, temp->content);
		break ;
		}
		temp = temp->next;
	}
	if (last  && temp->fd != fd)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		new->content = malloc(1);
		if (!new->content)
		{
			free(new);
			free(stash);
			return (NULL);
		}	
		new->content[0] = '\0';
		new->next = NULL;
		new->fd = fd;
		new->content = read_to_stash(fd, new->content);
		last->next = new;
	}                                                     
	if (temp)
	{
		if (findnline(temp->content))
			return (extract_line_and_update_stash(&temp->content));
		else if (temp->content[0] != '\0')
			return (extract_final_line(&temp->content));
		free(temp->content);
		temp->content = NULL;
		return (NULL);
	}
	free (temp->content);
	return (NULL);
}

int main()
{
	int fd1 = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd1));

	int fd2 = open("test2.txt", O_RDONLY);
	printf("%s", get_next_line(fd2));
	
	printf("%s", get_next_line(fd1));
}