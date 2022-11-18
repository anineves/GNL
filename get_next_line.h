#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif 

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>


char	*get_next_line(int fd);
char	*ft_read_file(int fd, char *backup);
char	*ft_line(char *backup);
char	*ft_remove(char *backup);
char	*ft_strjoin(char *s, char *buffer);
char    *ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

size_t	ft_strlen(const char *str);

#endif
