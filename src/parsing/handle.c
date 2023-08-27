/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   handle.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/27 14:33:11 by maroy                                    */
/*   Updated: 2023/08/27 14:44:17 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static uint8_t handle_quotes(t_minishell *minishell, char *c, int i)
{
	char *token;

	token = ft_strchr(minishell->argv[i], *c);
	if (token)
	{
		while (token)
		{
			ft_memmove(token, token + 1, ft_strlen(token));
			token = ft_strchr(minishell->argv[i], *c);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void    handle_dollar_sign(t_minishell *minishell, char *tmp, int i)
{
    size_t  len;
    char    *token;

    len = ft_strlen(minishell->argv[i]);
    token = ft_strchr(minishell->argv[i], '$');
    if (token != NULL)
    {
        tmp = getenv(++token);
        if (tmp)
        {
            free(minishell->argv[i]);
            return ;
        }
    }
    
}

void	expand_args(t_minishell *minishell)
{
	int	i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (minishell->argv[++i])
	{
		if (minishell->s_quotes >= 2 && handle_quotes(minishell, "\'", i))
			continue ;
		if (minishell->d_quotes >= 2)
			handle_quotes(minishell, "\"", i);
		if (!(ft_strncmp(minishell->argv[i], "$", 2) == 0))
			handle_dollar_sign(minishell, tmp, i);
		handle_home(minishell, tmp,  i);
	}
	minishell->argc = i;
	
}