#include "../../includes/asm.h"

static char	*check_label(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			;
		else if (line[i] == COMMENT_CHAR)
			return ("\0");
		else if (ft_strchr(LABEL_CHARS, line[i]) != NULL)
		{
			while (line[i] && ft_strchr(LABEL_CHARS, line[i]) != NULL)
				i++;
			if (line[i] && line[i] == LABEL_CHAR)
			{
				line = line + i + 1;
				i = -1;
			}
			else
				return (suppr_space_label_b(line, i));
		}
		else
			return (NULL);
		i++;
	}
	return ("\0");
}

static int	check_params_label_b(char **tmp, int i, int j, int count, t_asm *assm)
{
	if ((op_tab[i].args[j] == T_DIR
				|| op_tab[i].args[j] == T_DIR + T_REG
				|| op_tab[i].args[j] == T_DIR + T_IND
				|| op_tab[i].args[j] == T_DIR + T_REG + T_IND)
			&& check_t_dir_label(tmp[j], assm) == 1)
	{
		if (op_tab[i].label == 0)
			return (count + 4);
		else
			return (count + 2);
	}
	else if ((op_tab[i].args[j] == T_IND
				|| op_tab[i].args[j] == T_IND + T_REG
				|| op_tab[i].args[j] == T_IND + T_DIR
				|| op_tab[i].args[j] == T_IND + T_DIR + T_REG)
			&& check_t_ind_label(tmp[j], assm) == 1)
		return (count + 2);
	return (return_f("FATAL ERROR - an argument does not match with the opcode\n", -1));
}

static int	check_params_label(char **tmp, int i, t_asm *assm)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (-1);
		if ((op_tab[i].args[j] == T_REG
					|| op_tab[i].args[j] == T_REG + T_DIR
					|| op_tab[i].args[j] == T_REG + T_IND
					|| op_tab[i].args[j] == T_REG + T_IND + T_DIR)
				&& check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else
			count = check_params_label_b(tmp, i, j, count, assm);
		if (count < 0)
			return (-1);
		j++;
	}
	return (count);
}

int	check_label_2(char *line, t_asm *assm)
{
	char	**tmp;
	char	**pmt;
	int	count;
	int	i;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if (i > 15)
		return (-1);
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	free_tab(tmp);
	if ((count = check_params_label(pmt, i, assm)) < 0)
		return (-1);
	free_tab(pmt);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int		ft_third_turn(t_asm *assm, char *str)
{
	int	fd;
	int	r[2];

	assm->actual_bytes = 0;
	assm->line_error = 0;
	r[0] = 0;
	while (r[0] < assm->nb_label)
	{
		r[1] = 0;
		while (r[1] < assm->nb_label)
		{
			if (ft_strcmp(assm->label[r[0]].name, assm->label[r[1]].name) == 0 && r[0] != r[1])
				return (return_f("FATAL ERROR - same label name\n", -1));
			r[1]++;
		}
		r[0]++;
	}
	if ((fd = open(str, O_RDONLY)) < 3)
		exit(EXIT_SUCCESS);
	if (check_name(fd, &assm->line_error) < 0 || check_comment(fd, &assm->line_error) < 0)
		return (-1);
	if (ft_third_turn_b(assm, fd) < 0)
		return (-1);
	close(fd);
	return (0);
}

int	ft_third_turn_b(t_asm *assm, int fd)
{
	char	*line;
	char	*str_2;
	int	r;

	while (get_next_line(fd, &line))
	{
		assm->line_error = assm->line_error + 1;
		if ((str_2 = check_label(line, 0)) == NULL)
			return (return_f("FATAL ERROR - problem with the label\n", -1));
		if (ft_strcmp("\0", str_2) == 0)
			;
		else
		{
			if ((r = check_label_2(str_2, assm)) < 0)
				return (return_f("FATAL ERROR - argument call an inexistant label\n", -1));
			assm->actual_bytes = assm->actual_bytes + r;
			free(str_2);
		}
		free(line);
	}
	return (0);
}
