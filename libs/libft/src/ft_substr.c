/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_substr.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/20 16:36:03 by maroy                                    */
/*   Updated: 2023/07/31 11:42:04 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	ft_strlcpy(dst, s + start, len + 1);
	return (dst);
}
