/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_strtok.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/27 13:04:42 by maroy                                    */
/*   Updated: 2023/08/09 13:06:37 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save = NULL;
	char		*tmp;
	int			i;

	i = 0;
	if (str)
		save = str;
	if (!save)
		return (NULL);
	tmp = save;
	while (tmp[i] && !ft_strchr(delim, tmp[i]))
		i++;
	if (tmp[i])
	{
		tmp[i] = '\0';
		save = &tmp[i + 1];
	}
	else
		save = NULL;
	return (tmp);
}
