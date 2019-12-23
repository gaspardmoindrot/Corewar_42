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

static void	ft_print_in_file(char *file, unsigned char *tab, t_asm assm)
{
	int	h;
	int	fd;

	if ((fd = open(file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 3)
	{
		ft_putstr("error : can't open the file\n");
		exit(EXIT_SUCCESS);
	}
	h = -1;
	ft_putstr("Writing output program to ");
	ft_putstr(file);
	ft_putchar('\n');
        while (++h < PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm.len_bytes)
              ft_putchar_fd(tab[h], fd);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_asm	assm;
	int	i;

	i = -1;
	if (argc != 2)
		return (ft_error("usage: ./asm champion.s\n", 2));
	if (!(assm.file = change_s_cor(argv[1])))
		return (ft_error("error : your file is incorrect\n", 2));
	assm = first_turn(argv[1], assm);
	if (ft_error_first_turn(assm) == 0)
		return (0);
	if (ft_second_turn(&assm, argv[1]) < 0)
		return (ft_error("error : problem on file\n", 2));
	if (ft_third_turn(&assm, argv[1]) < 0)
		return (ft_error("error : problem on file\n", 2));
	if (!(assm.tab = (unsigned char *)malloc(sizeof(unsigned char) * (PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm.len_bytes))))
		return (ft_error("error : probleme de malloc\n", 2));
	while (++i < PROG_NAME_LENGTH + COMMENT_LENGTH + 16 + assm.len_bytes)
		assm.tab[i] = '\0';
	ft_print_binaire(&assm, argv[1]);
	ft_print_in_file(assm.file, assm.tab, assm);
	return (0);
}
