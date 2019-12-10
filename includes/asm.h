#ifndef ASM_H
# define ASM_H

#include "../libft/libft.h"
#include "op.h"
#include <fcntl.h>

# define OP(index)	op_tab[index]

typedef struct	s_label
{
	int	place;
	char	*name;
}		t_label;

typedef struct	s_asm
{
	char	*file;
	int	len_name;
	int	len_comment;
	int	len_bytes;
	int	actual_bytes;
	int	nb_label;
	t_label	*label;
}		t_asm;

int	ft_error(char *str, int fd);
char	*change_s_cor(char *str);
t_asm	first_turn(char *str);
int	check_comment(int fd);
int	check_name(int fd);
int	check_nothing(char *str);
int	ft_len_begin(char *line, char *str, int *quote);
int	check_nothing_before(char *line, char *str);
int	ft_len_next(char *line, int *quote);
int	check_instruc(int fd, t_asm *assm);
char	*suppr_space_label(char *line, t_asm *assm);
char	*suppr_space(char *line);
int	check_line_instruc(char *line);
int	check_params(char **tmp, int i);
int	check_t_ind(char *str);
int	check_t_dir(char *str);
int	check_t_reg(char *str);
int	ft_str_isdigit(char *str);

void	ft_name_label(char *line, t_asm *assm, int *j);
char	*stock_label(char *line, t_asm *assm, int *j);
int	ft_second_turn(t_asm *assm, char *str);

#endif
