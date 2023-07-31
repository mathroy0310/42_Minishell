/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_memchr.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/18 15:50:26 by maroy                                    */
/*   Updated: 2023/07/31 11:42:16 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	void			*b;

	if (!s)
		return (NULL);
	i = 0;
	str = (unsigned char *)s;
	b = NULL;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			b = &str[i];
			break ;
		}
		i++;
	}
	return (b);
}
