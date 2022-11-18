#include "get_next_line.h"

char		*ft_remove(char *backup)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (backup[i] && backup[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(backup) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buffer
	while (backup[i])
		line[j++] = backup[i++];
	free(backup);
	return (line);
}

// take line for return
char	*ft_get_line(char *backup)
{
	char	*line;
	int		size;

	size = 0;
	// if no line return NULL
	if (!*backup)
		return (NULL);
	// go to the eol
	while (backup[size] && backup[size] != '\n')
		size++;
	// malloc to eol
	line = ft_calloc(size + 2, sizeof(char));
	size = 0;
	// line = buffer
	while (backup[size] && backup[size] != '\n')
	{
		line[size] = backup[size];
		size++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (backup[size] == '\n')
		line[size++] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *backup)
{
	char	*buffer;
	int		byte_read;

	// malloc if res dont exist
	if (!backup)
		backup= ft_calloc(1, 1);
	// malloc buffer
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(backup, '\n'))
	{
		// while not eof read
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		// 0 to end for leak
		buffer[byte_read] = '\0';
		// join and free
		backup= ft_strjoin(backup, buffer);
		// quit if \n find
	
	}
	free(buffer);
	if (byte_read < 0)
		return (NULL);
	else
		return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	// error handling
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = ft_read_file(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_get_line(backup);
	backup = ft_remove(backup);
	return (line);
}

int main()
{
	int fd = open("a.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}
