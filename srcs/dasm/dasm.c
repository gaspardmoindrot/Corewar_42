/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:35:11 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 17:54:59 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int			ft_error(char *str, int fd, int error, int r)
{
	if (error >= 0)
	{
		ft_putstr_fd("\033[0;36m", fd);
		ft_putstr_fd("Problem on line : ", fd);
		ft_putnbr_fd(error, fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd("\033[0m", fd);
	}
	ft_putstr_fd("\033[0;33m", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\033[0m", fd);
	return (r);
}

int			return_f(char *str, int return_f)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	return (return_f);
}

static void	print_dasm(t_dasm *dasm)
{
	int	fd;
	int	i;

	i = 2;
	if ((fd = open(dasm->file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 3)
	{
		ft_putstr("\033[0;31merror : can't open last file\n\033[0m");
		exit(EXIT_SUCCESS);
	}
	ft_putstr("Writing reverse output program to ");
	ft_putstr(dasm->file);
	ft_putchar('\n');
	ft_putstr_fd(".name \"", fd);
	ft_putstr_fd(dasm->tab[0], fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(".comment \"", fd);
	ft_putstr_fd(dasm->tab[1], fd);
	ft_putstr_fd("\"\n\n", fd);
	while (i < dasm->nb_tab && ft_strlen(dasm->tab[i]) != 0)
	{
		ft_putstr_fd(dasm->tab[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}

short		free_op_tab(t_op *op_tab)
{
	free(op_tab[0].name);
	free(op_tab[1].name);
	free(op_tab[2].name);
	free(op_tab[3].name);
	free(op_tab[4].name);
	free(op_tab[5].name);
	free(op_tab[6].name);
	free(op_tab[7].name);
	free(op_tab[8].name);
	free(op_tab[9].name);
	free(op_tab[10].name);
	free(op_tab[11].name);
	free(op_tab[12].name);
	free(op_tab[13].name);
	free(op_tab[14].name);
	free(op_tab[15].name);
	free(op_tab[16].name);
	free(op_tab);
	return (1);
}

void		end_dasm(t_dasm *dasm, t_op *op_tab)
{
	print_dasm(dasm);
	free_tab(dasm->tab);
	free(dasm->file);
	free_op_tab(op_tab);
	close(dasm->fd);
}

int			main(int argc, char **argv)
{
	t_dasm	dasm;
	t_op	*op_tab;

	if (!(op_tab = init_op_tab()))
		return (0);
	if (argc != 2 && free_op_tab(op_tab))
		return (ft_error("usage: ./asm champion.s\n", 2, -1, 0));
	if ((dasm.fd = open(argv[1], O_RDONLY)) < 3 && free_op_tab(op_tab))
		return (ft_error("can't open the file\n", 2, -1, 0));
	if ((dasm.ret = read(dasm.fd, dasm.buf, COMMENT_LENGTH + PROG_NAME_LENGTH
			+ CHAMP_MAX_SIZE + 17)) < 0 && free_op_tab(op_tab))
		return (ft_error("can't read the file\n", 2, -1, 0));
	if (dasm.ret > COMMENT_LENGTH + PROG_NAME_LENGTH + CHAMP_MAX_SIZE + 16
			&& free_op_tab(op_tab))
		return (ft_error("file too big, there is a limit\n", 2, -1, 0));
	init_buffer(&dasm);
	if (!(dasm.file = change_cor_s(argv[1])) && free_op_tab(op_tab))
		return (ft_error("error : your file is incorrect\n", 2, -1, 0));
	dasm.tab = init_tab();
	if (begin(&dasm) == -1 && free_op_tab(op_tab))
		return (ft_error("error : your file is incorrect\n", 2, -1, 0));
	if (then(&dasm, op_tab) == -1 && free_op_tab(op_tab))
		return (ft_error("error : instructions are false\n", 2, -1, 0));
	end_dasm(&dasm, op_tab);
	return (0);
}
