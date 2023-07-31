/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_split.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/24 11:26:09 by maroy                                    */
/*   Updated: 2023/07/31 11:42:04 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*ft_add_strs(const char *s, char c, int *start)
{
	int		i;
	char	*str;
	int		j;

	if (!s || !start)
		return (NULL);
	i = 0;
	j = *start;
	while (s[j] == c)
		j++;
	while (s[j] && s[j] != c)
	{
		j++;
		i++;
	}
	str = ft_substr(s, j - i, i);
	*start = j;
	return (str);
}

static int	ft_wcount(const char *s, char c)
{
	int	i;
	int	words;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**strs;

	if (!s)
		return (NULL);
	i = 0;
	words = ft_wcount(s, c);
	strs = ft_calloc(sizeof(char *), words + 1);
	if (!strs)
		return (NULL);
	j = 0;
	while (i < words)
	{
		strs[i] = ft_add_strs(s, c, &j);
		i++;
	}
	return (strs);
}
