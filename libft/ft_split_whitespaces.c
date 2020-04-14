/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:22:30 by gmoindro          #+#    #+#             */
/*   Updated: 2019/05/03 18:12:21 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_white_space(char c)
{
	if (c == '\t' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

char		**ft_split_whitespaces(const char *str)
{
	char	**res;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	if ((res = malloc(sizeof(char*)
			* (ft_count_words((char *)str) + 1))) == NULL)
		return (NULL);
	while (str[i[0]])
	{
		while (is_white_space(str[i[0]]) && str[i[0]])
			i[0]++;
		if (str[i[0]])
		{
			i[2] = 0;
			if ((res[i[1]] = malloc(sizeof(char)
					* ft_ln_w((char *)str, i[0]) + 1)) == NULL)
				return (NULL);
			while (!(is_white_space(str[i[0]])) && str[i[0]])
				res[i[0]][i[2]++] = str[i[0]++];
			res[i[1]++][i[2]] = '\0';
		}
	}
	res[i[1]] = NULL;
	return (res);
}
