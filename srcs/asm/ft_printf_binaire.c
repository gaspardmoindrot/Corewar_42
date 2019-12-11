#include "../../includes/asm.h"

int	write_comment(int fd, t_asm *assm)
{
	char	*line;
	char	*str;
	int	comment;
	int	quote;
	int	i;
	int	len_comment;
	int	r;

	comment = 0;
	quote = 0;
	ft_print_in_actual("0\0", assm, 4);
	ft_print_in_actual(ft_itoa_base(assm->len_bytes, 16), assm, 4);
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (comment == 0 && (str = ft_strstr(line, COMMENT_CMD_STRING)))
		{
			comment++;
			if (check_nothing_before(line, COMMENT_CMD_STRING) == 0)
				return (-1);
			if ((len_comment = ft_write_begin(str, COMMENT_CMD_STRING, &quote, assm)) < 0)
				return (-1);
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_comment++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		else if (comment == 0 && ft_strstr(line, COMMENT_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (-1);
		}
		else
		{
			if ((r = ft_write_next(line, &quote, assm)) < 0)
				return (-1);
			len_comment = len_comment + r;
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_comment++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_comment);
			}
		}
		free(line);
	}
	return (-1);
}

int	ft_write_next(char *line, int *quote, t_asm *assm)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' && *quote < 2)
			*quote = *quote + 1;
		else if (*quote == 1)
		{
			assm->tab[assm->actual_bytes] = line[i];
			assm->actual_bytes++;
			len++;
		}
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

int	ft_write_begin(char *line, char *str, int *quote, t_asm *assm)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] && line[i] == str[i])
		i++;
	while (line[i])
	{
		if (line[i] == '"' && *quote < 2)
			*quote = *quote + 1;
		else if (*quote == 1)
		{
			assm->tab[assm->actual_bytes] = line[i];
			assm->actual_bytes++;
			len++;
		}
		else if (line[i] == COMMENT_CHAR)
			break;
		else if (*quote != 1 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (len);
}

unsigned char	ft_deci(char c10, char c1)
{
	if (c10 == 'A' || c10 == 'B' || c10 == 'C' || c10 == 'D' || c10 == 'E' || c10 == 'F')
		c10 = c10 - 55;
	else
		c10 = c10 - 48;
	if (c1 == 'A' || c1 == 'B' || c1 == 'C' || c1 == 'D' || c1 == 'E' || c1 == 'F')
		c1 = c1 - 55;
	else
		c1 = c1 - 48;
	return (c10 * 16 + c1);
}

void		ft_print_in_actual(char *str, t_asm *assm, int size)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (len - 1 >= 0)
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci(str[len - 1], str[len]);
			len = len - 2;
		}
		else
		{
			assm->tab[assm->actual_bytes + size - i] = ft_deci('0', str[len]);
			len--;
		}
		i++;
	}
	assm->actual_bytes = assm->actual_bytes + size;
}

int	write_name(int fd, t_asm *assm)
{
	char	*line;
	char	*str;
	int	name;
	int	quote;
	int	i;
	int	len_name;
	int	r;

	name = 0;
	quote = 0;
	ft_print_in_actual(ft_itoa_base(COREWAR_EXEC_MAGIC, 16), assm, 4);
	while (get_next_line(fd, &line))
	{
		i = 0;
		if (name == 0 && (str = ft_strstr(line, NAME_CMD_STRING)))
		{
			name++;
			if (check_nothing_before(line, NAME_CMD_STRING) == 0)
				return (-1);
			if ((len_name = ft_write_begin(str, NAME_CMD_STRING, &quote, assm)) < 0)
				return (-1);
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_name++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		else if (name == 0 && ft_strstr(line, NAME_CMD_STRING) == NULL)
		{
			if (check_nothing(line) == 0)
				return (-1);
		}
		else
		{
			if ((r = ft_write_next(line, &quote, assm)) < 0)
				return (-1);
			len_name = len_name + r;
			if (quote == 1)
			{
				assm->tab[assm->actual_bytes] = '\n';
				assm->actual_bytes++;
				len_name++;
			}
			if (quote == 2)
			{
				free(line);
				return (len_name);
			}
		}
		free(line);
	}
	return (-1);
}

int	ft_print_binaire(t_asm *assm, char *str)
{
	int	fd;

	assm->actual_bytes = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("error : can't open the file\n");
		exit(EXIT_SUCCESS);
	}
	write_name(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + 4;
	write_comment(fd, assm);
	assm->actual_bytes = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	//
	//
	close(fd);
	return (0);
}
