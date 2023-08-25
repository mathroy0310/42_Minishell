/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_count_words.c                                  ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/24 16:27:15 by maroy                                    */
/*   Updated: 2023/08/24 16:28:51 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(charset, str[i]) == NULL)
		{
			count++;
			while (str[i] && ft_strchr(charset, str[i]) == NULL)
				i++;
		}
		else
			i++;
	}
	return (count);
}