/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_memcpy.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/18 12:06:48 by maroy                                    */
/*   Updated: 2023/07/31 11:42:04 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst1;
	char	*src1;

	i = 0;
	if (!dst || !src)
		return (dst);
	dst1 = (char *)dst;
	src1 = (char *)src;
	if (dst1 == src1)
		return (dst1);
	while (i < len)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}
