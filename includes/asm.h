/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:10:46 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:21 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

# define OP(index)	op_tab[index]

typedef struct		s_label
{
	int				place;
	char			*name;
}					t_label;

typedef struct		s_asm
{
	unsigned char	*tab;
	char			*file;
	int				fd_file;
	int				len_name;
	int				len_comment;
	int				len_bytes;
	int				actual_bytes;
	int				actual_bytes_l;
	int				nb_label;
	int				line_error;
	t_label			*label;
}					t_asm;

int					ft_error(char *str, int fd, int a);
char				*change_s_cor(char *str);
t_asm				first_turn(char *str, t_asm assm);
int					check_comment(int fd, int *error);
int					check_name(int fd, int *error);
int					check_nothing(char *str);
int					ft_len_begin(char *line, char *str, int *quote);
int					check_nothing_before(char *line, char *str);
int					ft_len_next(char *line, int *quote);
int					check_instruc(int fd, t_asm *assm);
char				*suppr_space_label(char *line, t_asm *assm, int i);
char				*suppr_space(char *line, int i);
int					check_line_instruc(char *line);
int					check_params(char **tmp, int i);
int					check_t_ind(char *str);
int					check_t_dir(char *str);
int					check_t_reg(char *str);
int					ft_str_isdigit(char *str);
void				ft_name_label(char *line, t_asm *assm, int *j);
char				*stock_label(char *line, t_asm *assm, int *j, int i);
int					ft_second_turn(t_asm *assm, char *str);
int					check_t_dir_label(char *str, t_asm *assm);
int					check_t_ind_label(char *str, t_asm *assm);
int					ft_third_turn(t_asm *assm, char *str);
int					ft_print_binaire(t_asm *assm, char *str);
int					write_comment(int fd, t_asm *assm);
int					ft_write_next(char *line, int *quote, t_asm *assm);
int					ft_write_begin(char *line, char *str, int *q, t_asm *assm);
unsigned char		ft_deci(char c10, char c1);
void				ft_print_in_actual(char *str, t_asm *assm, int size);
int					write_name(int fd, t_asm *assm);
int					print_instruc(int fd, t_asm *assm);
unsigned long		puissance(unsigned long nb, int p);
void				ft_char_argu(char **tmp, int i, t_asm *assm);
int					print_t_reg(char *str, t_asm *assm);
int					print_t_dir(char *str, t_asm *assm, int j);
int					print_t_ind(char *str, t_asm *assm);
void				print_nb_bytes(int bytes, t_asm *assm, unsigned int nb);
void				ft_print_params(char **tmp, int i, t_asm *assm);
int					print_line_instruc(char *line, t_asm *assm);
int					print_instruc(int fd, t_asm *assm);
int					return_f(char *str, int return_f);
void				free_tab(char **tab);
void				ft_print_in_file(char *file, unsigned char *ta, t_asm assm);
char				*ft_put_together(char **res);
int					check_label_2(char *line, t_asm *assm);
char				*ft_put_together_b(char *str, char **res);
char				*suppr_space_label_b(char *line, int i);
char				*suppr_space_b(char *line, int j);
int					check_params_b(char **tmp, int i, int j, int count);
char				*stock_label_b(char *line, int i);
int					ft_second_turn_b(t_asm *assm, int fd, int i);
int					ft_third_turn_b(t_asm *assm, int fd);
int					check_no_space_number(char **tab, int i, int com);
char				*ft_return_space(char *str);
void				free_global(t_asm *assm, int nb);

#endif
