/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_strtok.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/27 13:04:42 by maroy                                    */
/*   Updated: 2023/08/18 13:09:38 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_pos;
	char		*token;

	if (str)
		last_pos = str;
	token = last_pos;
	while (*last_pos)
	{
		if (ft_strchr(delim, *last_pos))
		{
			*last_pos = '\0';
			last_pos++;
			if (*token)
				return (token);
			token = last_pos;
		}
		else
			last_pos++;
	}
	if (*token)
		return (token);
	return (NULL);
}
