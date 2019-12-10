#include "../../includes/asm.h"

static int	ft_strrchr_nbr(const char *s, int c)
{
	int i;
	int res;

	i = 0;
	res = -1;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (i);
	}
	while (s[i])
	{
		if (s[i] == (char)c)
			res = i;
		i++;
	}
	if (res == -1)
		return (-1);
	return (res);
}

char		*change_s_cor(char *str)
{
	int	i;
	char	*s;

	i = 0;
	if (ft_strchr(str, '.') == NULL)
		return (NULL);
	if (ft_strcmp(ft_strrchr(str, '.'), ".s"))
		return (NULL);
	s = ft_strsub(str, 0, ft_strrchr_nbr(str, '.'));
	s = ft_strcat(s, ".cor");
	return (s);
}
