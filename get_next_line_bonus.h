#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif



char	*get_next_line(int fd);
char	*free_and_return_null(char *ptr1, char *ptr2);
char	*read_to_stash(int fd, char *stash);
char	*extract_line_and_update_stash(char **stash);
char	*extract_final_line(char **stash);

int		countToNewLine(char *str);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		findnline(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);

#endif
