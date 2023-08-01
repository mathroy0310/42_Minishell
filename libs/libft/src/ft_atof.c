/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_atof.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 15:49:38 by maroy                                    */
/*   Updated: 2023/08/01 15:54:31 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

static float	parse_fraction(const char *str, int *index)
{
	float	res;
	float	fraction;
	int		i;

	res = 0;
	fraction = 0.1;
	i = *index;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += (str[i++] - '0') * fraction;
		fraction *= 0.1;
	}
	*index = i;
	return (res);
}

float	ft_atof(const char *str)
{
	float	res;
	int		i;
	int		s;

	res = 0;
	i = 0;
	s = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		res += parse_fraction(str, &i);
	}
	return (s * res);
}
