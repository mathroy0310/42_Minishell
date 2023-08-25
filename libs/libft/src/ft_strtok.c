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
	char	*token;

	token = str;
	if (ft_strchr(str, *delim) != NULL)
		token = ft_substr(str, 0, ft_strchr(str, *delim) - str);
	else
		token = ft_strdup(str);
	return (token);
}
