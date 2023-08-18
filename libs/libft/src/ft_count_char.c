/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_count_char.c                                   ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/17 16:32:14 by maroy                                    */
/*   Updated: 2023/08/18 17:09:08 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_count_char(char *s, char c)
{
	if (*s == '\0')
		return (0);
	else
	{
		if (*s == c)
			return (ft_count_char(s + 1, c) + 1);
		else
			return (ft_count_char(s + 1, c));
	}
}
