/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_atoi.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/18 16:10:02 by maroy                                    */
/*   Updated: 2023/07/31 11:37:16 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		res;
	char	*cstr;

	if (!str)
		return (0);
	cstr = (char *)str;
	i = 0;
	s = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (cstr[i] == '-' || cstr[i] == '+')
	{
		if (cstr[i] == '-')
			s = -s;
		i++;
	}
	while (ft_isdigit(cstr[i]))
	{
		res = res * 10 + cstr[i] - '0';
		i++;
	}
	return (s * res);
}
