#include "../../includes/asm.h"

void	ft_name_label(char *line, t_asm *assm, int *j)
{
	int	i;

	i = 0;
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		i++;
	if (!(assm->label[*j].name = (char *)malloc(sizeof(char) * (i + 1))))
		exit(EXIT_SUCCESS);
	assm->label[*j].name[i] = '\0';
	i = 0;
	while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
	{
		assm->label[*j].name[i] = line[i];
		i++;
	}
}

char	*stock_label(char *line, t_asm *assm, int *j)
{
	int     i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] == LABEL_CHAR)
			{
				ft_name_label(line, assm, j);
				assm->label[*j].place = assm->actual_bytes + 1;
				*j = *j + 1;
				line = line + i + 1;
				i = -1;
			}
			else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
				return (suppr_space(line));
			else
				return (NULL);
		}
		else
			return (NULL);
		i++;
	}
	return ("\0");
}

int	ft_second_turn(t_asm *assm, char *str)
{
	char	*line;
	int	i;
	int	fd;
	int	r;

	assm->actual_bytes = 0;
	i = 0;
	if ((fd = open(str, O_RDONLY)) < 3)
	{
		ft_putstr("error : can't open the file\n");
		exit(EXIT_SUCCESS);
	}
	if (!(assm->label = (t_label *)malloc(sizeof(t_label) * assm->nb_label)))
		return (-1);
	if (check_name(fd) < 0)
		return (-1);
	if (check_comment(fd) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		if ((line = stock_label(line, assm, &i)) == NULL)
			return (-1);
		if (ft_strcmp("\0", line) == 0)
			;
		else
		{
			if ((r = check_line_instruc(line)) < 0)
				return (-1);
			assm->actual_bytes = assm->actual_bytes + r;
		}
	}
	close(fd);
	return (0);
}
