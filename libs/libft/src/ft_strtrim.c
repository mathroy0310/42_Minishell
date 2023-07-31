/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_strtrim.c                                      ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/24 10:56:07 by maroy                                    */
/*   Updated: 2023/07/31 11:42:22 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trmd;
	size_t	i;
	size_t	f;
	size_t	l;

	if (!s1 || !set)
		return (NULL);
	f = 0;
	l = ft_strlen(s1);
	while (s1[f] && ft_isset(s1[f], set))
		f++;
	while (l > f && ft_isset(s1[l - 1], set))
		l--;
	trmd = malloc(sizeof(char) * (l - f + 1));
	if (trmd == NULL)
		return (NULL);
	i = 0;
	while (f < l)
		trmd[i++] = s1[f++];
	trmd[i] = 0;
	return (trmd);
}
