/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/23 16:35:22 by maroy                                    */
/*   Updated: 2023/08/27 13:20:30 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_double_redir(char *src, char **dest, int *i, int *n_tokens)
{
	dest[*n_tokens] = malloc(sizeof(char) * (3));
    if (src[*i] == '>')
	    ft_strlcpy(dest[(*n_tokens)++], ">>", 3);
	else if (src[*i] == '<')
	    ft_strlcpy(dest[(*n_tokens)++], "<<", 3);
	*i += 2;
	dest[*n_tokens] = ft_strtok(&src[*i], " ");
	*i += ft_strlen(dest[(*n_tokens)++]) - 1;
}

void	parse_single_token(char *src, char **dest, int *i, int *n_tokens)
{
	dest[*n_tokens] = malloc(sizeof(char) * (2));
	ft_strlcpy(dest[(*n_tokens)++], &src[(*i)++], 2);
	dest[*n_tokens] = ft_strtok(&src[*i], " ");
	*i += ft_strlen(dest[(*n_tokens)++]) - 1;
}

void	parse_inner_tokens(char *src, char **dest, int *i, int *n_tokens)
{
	int	size;
	int	start;

	size = ft_strchr(&src[*i], ' ') - &src[*i];
	if (size < 0 || size > 300)
		size = ft_strlen(&src[*i]);
	start = *i;
	while (size--)
	{
		if (src[*i] == '>' || src[*i] == '<' || src[*i] == '|')
		{
			if (*i != start)
				dest[(*n_tokens)++] = ft_strtok(&src[start], &src[*i]);
			if (src[*i + 1] && (src[*i + 1] == '>' || src[*i + 1] == '<')&& src[*i + 2] != ' ')
				return (parse_double_redir(src, dest, i, n_tokens));
			return (parse_single_token(src, dest, i, n_tokens));
		}
		*i += 1;
	}
	*i = start;
	dest[*n_tokens] = ft_strtok(&src[*i], " ");
	*i += ft_strlen(dest[(*n_tokens)++]) - 1;
}

static void	parse_token(char *src, char **dest, int *i, int *n_tokens)
{
	int		size;
	char	*end;

	if (src[*i + 1] && (src[*i] == '\'' || src[*i] == '\"')
		&& (ft_strchr(&src[*i + 1], '\'') || ft_strchr(&src[*i + 1], '\"')))
	{
		end = ft_strchr(&src[*i + 1], src[*i]);
		size = end - &src[*i] + 2;
		dest[*n_tokens] = (char *)ft_calloc(size, sizeof(char));
		ft_strlcpy(dest[(*n_tokens)++], &src[*i], size);
		*i += size - 2;
	}
	else
		parse_inner_tokens(src, dest, i, n_tokens);
}

void	parsing(char *src, char **dest)
{
	int		i;
	int		n_tokens;

	i = -1;
	n_tokens = 0;
	while (src[++i])
	{
		while (src[i] == ' ' || src[i] == '\t' || src[i] == '\a'
			|| src[i] == '\r' || src[i] == '\v' || src[i] == '\f')
			i++;
		parse_token(src, dest, &i, &n_tokens);
	}
	dest[n_tokens] = NULL;
	while (dest[++n_tokens])
		free(dest[n_tokens]);
}
