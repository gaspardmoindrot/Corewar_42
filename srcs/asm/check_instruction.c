/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:47:26 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:47:42 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int			check_no_space_number(char **tab, int i, int com)
{
	if (i == 0 || i == 1 || com > 0)
		return (1);
	if (tab[i][0] == 'r' || tab[i][0] == DIRECT_CHAR
			|| tab[i][0] == SEPARATOR_CHAR)
		return (1);
	if (tab[i - 1][ft_strlen(tab[i - 1]) - 1] != ',')
		return (-1);
	return (1);
}

char		*ft_return_space(char *str)
{
	str[0] = 'A';
	str[1] = '\0';
	return (str);
}

char		*ft_put_together_b(char *str, char **res)
{
	int		tab[4];

	tab[3] = 0;
	tab[0] = 0;
	tab[1] = 0;
	while (res[tab[0]])
	{
		tab[2] = 0;
		while (res[tab[0]][tab[2]])
		{
			str[tab[1]] = res[tab[0]][tab[2]];
			if (res[tab[0]][tab[2]] == COMMENT_CHAR)
				tab[3]++;
			tab[1]++;
			tab[2]++;
		}
		if (tab[0] == 0)
			str[tab[1]] = ' ';
		if (tab[0] == 0)
			tab[1]++;
		if (check_no_space_number(res, tab[0], tab[3]) < 0)
			return (ft_return_space(str));
		tab[0]++;
	}
	return (str);
}

char		*ft_put_together(char **res)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (res[i])
	{
		len = len + ft_strlen(res[i]);
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	str[len + 1] = '\0';
	str = ft_put_together_b(str, res);
	return (str);
}

short		free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

static char	*ft_strcat_mal(char *s1, const char *s2)
{
	int		len;
	int		i;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (i < len && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] && i < (int)ft_strlen(s2))
	{
		str[len + i] = ((char *)s2)[i];
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char		*suppr_space_b(char *line, int j)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
		return (NULL);
	while (i < j)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = ' ';
	i++;
	while (line[i - 1])
	{
		str[i] = line[i - 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*suppr_space(char *line, int j)
{
	char	**res;
	char	**res_2;
	char	*str[3];
	int		i;

	if (line[j] == '-' || line[j] == DIRECT_CHAR)
	{
		if (!(str[1] = suppr_space_b(line, j)))
			return (NULL);
	}
	else
		str[1] = ft_strcat_mal("\0", line);
	i = 0;
	res = ft_split_whitespaces(str[1]);
	free(str[1]);
	str[0] = ft_put_together(res);
	free_tab(res);
	res_2 = ft_strsplit(str[0], '#');
	free(str[0]);
	str[2] = ft_strcat_mal("\0", res_2[0]);
	free_tab(res_2);
	return (str[2]);
}

char		*suppr_space_label_b(char *line, int i)
{
	if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '-' || line[i] == DIRECT_CHAR)
		return (suppr_space(line, i));
	return (NULL);
}

char		*suppr_space_label(char *line, t_asm *assm, int i)
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
				assm->nb_label++;
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

int			check_params_b(char **tmp, int i, int j, int count)
{
	if ((op_tab[i].args[j] == T_DIR
		|| op_tab[i].args[j] == T_DIR + T_REG
		|| op_tab[i].args[j] == T_DIR + T_IND
		|| op_tab[i].args[j] == T_DIR + T_REG + T_IND)
			&& check_t_dir(tmp[j]) == 1)
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
			&& check_t_ind(tmp[j]) == 1)
		return (count + 2);
	return (return_f("FATAL ERROR - not match with the opcode\n", -1));
}

int			check_params(char **tmp, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j] != NULL)
	{
		if (j + 1 > op_tab[i].nb_arg)
			return (return_f("FATAL ERROR - too much params\n", -1));
		if ((op_tab[i].args[j] == T_REG || op_tab[i].args[j] == T_REG + T_DIR
					|| op_tab[i].args[j] == T_REG + T_IND
					|| op_tab[i].args[j] == T_REG + T_IND + T_DIR)
				&& check_t_reg(tmp[j]) == 1)
			count = count + 1;
		else
			count = check_params_b(tmp, i, j, count);
		if (count < 0)
			return (-1);
		j++;
	}
	if (j != op_tab[i].nb_arg)
		return (return_f("FATAL ERROR - too few arguments\n", -1));
	return (count);
}

int			check_line_instruc(char *line)
{
	char	**tmp;
	char	**pmt;
	int		count;
	int		i;
	int		len;

	count = 0;
	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (op_tab[i].nb_arg != 0 && (ft_strcmp(tmp[0], op_tab[i].name) != 0))
		i++;
	if ((i > 15 || tmp[1] == NULL) && free_tab(tmp))
		return (return_f("FATAL ERROR - opcode unknown\n", -1));
	len = ft_strlen(tmp[1]);
	if (tmp[1][len - 1] == ',' && free_tab(tmp))
		return (return_f("FATAL ERROR - there is a final coma\n", -1));
	pmt = ft_strsplit(tmp[1], SEPARATOR_CHAR);
	free_tab(tmp);
	if ((count = check_params(pmt, i)) < 0 && free_tab(pmt))
		return (-1);
	free_tab(pmt);
	count++;
	if (op_tab[i].nb_arg > 1)
		count++;
	return (count);
}

int			check_instruc(int fd, t_asm *assm)
{
	char	*line;
	char	*str;
	int		r;

	r = 0;
	while (get_next_line(fd, &line) > 0)
	{
		assm->line_error++;
		if ((str = suppr_space_label(line, assm, 0)) == NULL && f_l(&line))
			return (return_f("FATAL ERROR - wrong syntax line\n", -1));
		if (ft_strcmp("\0", str) == 0)
			;
		else
		{
			if ((r = check_line_instruc(str)) < 0 && f_l(&str)
					&& f_l(&line))
				return (-1);
			assm->len_bytes = assm->len_bytes + r;
			free(str);
		}
		free(line);
	}
	if (assm->len_bytes == 0)
		return (return_f("FATAL ERROR - no instructions\n", -1));
	return (assm->len_bytes);
}
