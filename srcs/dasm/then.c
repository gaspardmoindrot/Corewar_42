#include "../../includes/dasm.h"

int	write_opcode(t_dasm *dasm, int opcode)
{
	int	i;

	i = 0;
	while (op_tab[opcode - 1].name[i])
	{
		dasm->tab[nb_tab][i] = op_tab[opcode - 1].name[i];
		i++;
	}
	dasm->tab[nb_tab][i] = ' ';
	return (i + 1);
}

void	write_big_arg(t_dasm *dasm, int nb_inst, int opcode, int j, int i)
{
}

void	write_small_arg(t_dasm *dasm, int opcode, int j, int i)
{
	if (op_tab[opcode - 1].args[1] == 1)
		write_reg(dasm, j, i);
	else if (op_tab[opcode - 1].args[1] == 2)
		write_dir(dasm, j, i);
	else (op_tab[opcode - 1].args[1] == 3)
		write_ind(dasm, j, i);
}

int	instruct_alone(t_dasm *dasm, int i)
{
	int	j;
	int	nb_inst;
	int	opcode;

	j = 0;
	nb_inst = dasm->buf[i + 1];
	opcode = dasm->buf[i];
	if (opcode < 1 || opcode > 16
			|| (nb_inst < 1 && op_tab[opcode - 1].nb_arg != 1))
		return (return_f("FATAL ERROR : unknown opcode\n", -1));
	j = write_opcode(dasm, opcode);
	if (op_tab[opcode - 1].nb_arg > 1)
		write_big_arg(dasm, nb_inst, opcode, j, i);
	else
		write_small_arg(dasm, opcode, j, i);
}

int	then(t_dasm *dasm)
{
	int	i;
	int	bis;

	dasm->nb_tab = 2;
	i = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	while (i < assm->ret)
	{
		if ((bis = instuct_alone(dasm, i)) == -1)
			return (-1);
		i = i + bis;
		dasm->nb_tab++;
	}
	if (i != assm->ret)
		return (-1);
	return (0);
}
