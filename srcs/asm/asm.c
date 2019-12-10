#include "../../includes/asm.h"

int	ft_error(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	return (0);
}

int	ft_error_first_turn(t_asm assm)
{
	if (assm.len_name < 0 || assm.len_comment < 0 || assm.len_bytes < 0)
		return (ft_error("error : problem on file\n", 2));
	if (assm.len_name > PROG_NAME_LENGTH)
		return (ft_error("error : name too big\n", 2));
	if (assm.len_comment > COMMENT_LENGTH)
		return (ft_error("error : comment too big\n", 2));
	return (1);
}

int	main(int argc, char **argv)
{
	t_asm	assm;

	if (argc != 2)
		return (ft_error("usage: ./asm champion.s\n", 2));
	if (!(assm.file = change_s_cor(argv[1])))
		return (ft_error("error : your file is incorrect\n", 2));
	assm = first_turn(argv[1]);
	if (ft_error_first_turn(assm) == 0)
		return (0);
	if (ft_second_turn(&assm, argv[1]) < 0)
		return (ft_error("error : problem on file\n", 2));
	ft_printf("\nOK jusque la !\n\n");
	return (0);
}
