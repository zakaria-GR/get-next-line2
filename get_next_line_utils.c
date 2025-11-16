#include "get_next_line.h"

int index_of_newline(char *str)
{
    int i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    return i;
}

size_t	ft_strlen(const char *str)
{
    size_t	i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int	has_newline(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\n')
            return 1;
        i++;
    }
    return 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    size_t	i = 0, y = 0;
    size_t	s1_len = ft_strlen(s1);
    size_t	s2_len = ft_strlen(s2);
    char	*s3 = malloc((s1_len + s2_len + 1) * sizeof(char));

    if (!s1 || !s2 || !s3)
        return (NULL);
    while (i < s1_len)
        s3[i] = s1[i], i++;
    while (i < s1_len + s2_len)
        s3[i++] = s2[y++];
    s3[i] = '\0';
    return (s3);
}

void	*ft_calloc(size_t count, size_t size)
{
    unsigned char	*temp;
    size_t			i = 0;

    if (count && count > SIZE_MAX / size)
        return (NULL);
    temp = malloc(count * size);
    if (!temp)
        return (NULL);
    while (i < (count * size))
        temp[i++] = 0;
    return (temp);
}
