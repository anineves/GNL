#include "get_next_line.h"

//remove a linha lida. Ela recebe como parâmetro a static , 
//nela eu procuro até a quebra de linha \n ou até chegar no final,
//se chega a EOF, dou um free na variável e retorno NULL , senão, 
//eu malloco uma nova variavel com o (tamanho total de backup, menos o tamanho da linha),
//copio o restante de backup pra uma nova variável e dou free nela.
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
// Como parâmetro ainda vamos usar o backup, faço uma verificação se a backup 
//não está com o primeiro caracter como null byte ('\0')
//percorro ela inteira até achar uma ('\n') ou o final dela, 
//crio com o malloc uma string com o tamanho que li + 2 espaços, pra caso haja um \n ,
//eu coloque ele e logo em seguida o (\0) e retorno essa linha.
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
//Ler arquivo
//recebe como parâmetro o fd do arquivo e a variavel estática.
//crio um buffer com o tamnaho do BUFFER_SIZE e uso a função read() 
//pra ler o arquivo até encontrar o final dele - que seria retornado 0 - ou até encontrar uma linha (\n)
//caso ocorra algum erro, o laço de repetição é parado pois vai ser retornado -1,
//free a variavel buffer que tinha mallocado e retorno NULL,
//caso contrário, uso a função ft_strjoin()(onde adicionei free) para juntar o conteúdo de backup com o buffer.
char	*ft_read_file(int fd, char *backup)
{
	char	*buffer;
	int		byte_read;

	if (!backup)
		backup= ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1; //inicializo em 1 para entrar no loop pela primeira ve
	while (byte_read > 0 && !ft_strchr(backup, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < -1) // porque se read der erro devolve 0
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
