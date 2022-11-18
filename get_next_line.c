#include "get_next_line.h"

char		*ft_remove(char *backup)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(backup) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (backup[i])
		line[j++] = backup[i++];
	free(backup);
	return (line);
}

// bBuscar linha parea returnar
char	*ft_get_line(char *backup)
{
	char	*line;
	int		size;

	size = 0;
	if (!*backup)
		return (NULL);
	while (backup[size] && backup[size] != '\n')
		size++;
	line = ft_calloc(size + 2, sizeof(char));
	size = 0;
	while (backup[size] && backup[size] != '\n')
	{
		line[size] = backup[size];
		size++;
	}
	if (backup[size] == '\n')
		line[size++] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *backup)
{
	char	*buffer;
	int		byte_read;

	if (!backup)
		backup= ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(backup, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		backup= ft_strjoin(backup, buffer);
	
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
	int fd = open("teste.txt", O_RDONLY);
	printf("linha1 %s", get_next_line(fd));
	printf("linha2 %s", get_next_line(fd));
	printf("linha3 %s", get_next_line(fd));
	printf("linha4 %s", get_next_line(fd));
	return 0;
}
