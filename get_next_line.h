#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		index_of_newline(char *str);
size_t	ft_strlen(const char *str);
int		has_newline(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);

char	*read_to_stash(int fd, char *stash);
char	*get_line_from_stash(char *stash);
char	*trim_stash(char *stash);
char	*get_next_line(int fd);

#endif
