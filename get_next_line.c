#include "get_next_line.h"

char *read_to_stash(int fd, char *stash)
{
    ssize_t nb_read;
    char    *buff;
    char    *temp;

    buff = malloc(BUFFER_SIZE + 1);
    if (!buff)
        {
            free(stash);
            return (NULL);
        }
    while (!has_newline(stash))
    {
        nb_read = read(fd, buff, BUFFER_SIZE);
        if (nb_read == 0)
            break;
        if (nb_read < 0)
        {
            free(stash);
            free(buff);
            return (NULL);
        }
        buff[nb_read] = '\0';
        temp = ft_strjoin(stash, buff);
        if (!temp)
        {
            free(buff);
            free(stash);
            return (NULL);
        }
        free(stash);
        stash = temp;
    }
    free(buff);
    return (stash);
}

char	*get_line_from_stash(char *stash)
{
    int	i, y, start;
    char	*line;

    if (!stash || stash[0] == '\0')
        return NULL;

    if (has_newline(stash))
    {
        y = index_of_newline(stash) + 1;
        line = ft_calloc(y + 1, 1);
        if (!line)
            return (NULL);
        start = 0;
        while (start < y)
        {
            line[start] = stash[start], 
            start++;
        }
        line[start] = '\0';
        return line;
    }
    i = ft_strlen(stash);
    line = ft_calloc(i + 1, 1);
    if (!line)
        return NULL;
    start = 0;
    while (start < i)
        line[start] = stash[start], start++;
    line[start] = '\0';
    return line;
}

char *trim_stash(char *stash)
{
    int start;
    int i;
    int len;
    char *leftover;

    if (!stash)
        return NULL;
    if (!has_newline(stash))
    {
        free(stash);
        return NULL;
    }
    len = ft_strlen(stash);
    start = index_of_newline(stash) + 1;
    leftover = ft_calloc(len - start + 1, 1);
    if (!leftover)
    {
        free(stash);
        return NULL;
    }
    i = 0;
    while (stash[start])
        leftover[i++] = stash[start++];
    free(stash);
    return leftover;
}

char *get_next_line(int fd)
{
    static char *stash;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (!stash)
    {
        stash = malloc(1);
        if (!stash)
            return NULL;
        stash[0] = '\0';
    }
    stash = read_to_stash(fd, stash);
    if (!stash)
        return NULL;

    line = get_line_from_stash(stash);
    stash = trim_stash(stash);
    return line;
}
