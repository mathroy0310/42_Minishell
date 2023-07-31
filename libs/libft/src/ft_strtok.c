/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_strtok.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/27 13:04:42 by maroy                                    */
/*   Updated: 2023/07/31 14:15:44 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token;
	char		*end_token;

	last_token = NULL;
	if (str == NULL)
		str = last_token;
	while (*str && ft_strchr(delim, *str))
		++str;
	if (!*str)
		return (NULL);
	end_token = str;
	while (*end_token && !ft_strchr(delim, *end_token))
		++end_token;
	if (!*end_token)
		last_token = NULL;
	else
	{
		*end_token = '\0';
		last_token = end_token + 1;
	}
	return (str);
}
