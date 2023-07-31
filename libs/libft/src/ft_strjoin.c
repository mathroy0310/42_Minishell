/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_strjoin.c                                      ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/21 01:23:46 by maroy                                    */
/*   Updated: 2023/07/31 12:21:48 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			lens1;
	int			lens2;
	char		*dst;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dst = malloc(lens1 + lens2 + 1);
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1, lens1);
	ft_memmove(dst + lens1, s2, lens2);
	dst[lens1 + lens2] = '\0';
	return (dst);
}
