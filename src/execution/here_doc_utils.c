/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   here_doc_utils.c                                  ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/19 22:47:32 by maroy                                    */
/*   Updated: 2023/10/28 19:06:16 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

int	token_type_count(t_cmd *cmd, t_token_type type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->redir[i].type == type)
			j++;
		i++;
	}
	return (j);
}

static char	*invalid_envar_here_doc(char *buff, int i)
{
	char	*str;

	str = ft_strdup("");
	if (buff[i] == '?')
		str = ft_strjoin_free(str, ft_itoa(g_global->exit_status));
	else
	{
		i += 1;
		while (buff[i] != '\0' && buff[i] != SPACE)
		{
			str = ft_strjoin_char(str, buff[i]);
			i++;
		}
	}
	return (str);
}

static char	*envar_helper(char *buff, int *i, char *str, int flag)
{
	char	*temp;
	char	*env;

	if (flag == 0)
	{
		temp = invalid_envar_here_doc(buff, (*i));
		(*i) += ft_strlen(temp) - 1;
		return (ft_strjoin_free(str, temp));
	}
	else
	{
		env = ft_strdup("");
		while (buff[*i] != '\0' && is_valid_envar(buff[*i]))
		{
			env = ft_strjoin_char(env, buff[(*i)]);
			(*i)++;
		}
		str = ft_strjoin_free(str, ft_getenv(env));
		free(env);
		return (str);
	}
	return (NULL);
}

static char	*handle_envar(char *buff, int *i, char *str)
{
	(*i)++;
	if (ft_isdigit(buff[*i]) || buff[*i] == '?' || !is_valid_envar(buff[*i]))
		str = envar_helper(buff, i, str, 0);
	else
	{
		str = envar_helper(buff, i, str, 2);
		if (buff[*i] != '\0')
			str = ft_strjoin_char(str, buff[*i]);
	}
	return (str);
}

char	*envar_here_doc(char *buff, int i)
{
	char	*str;

	if (buff == NULL)
		return (ft_strdup(buff));
	if (*buff == '\0')
		return (ft_strdup(buff));
	str = ft_strdup("");
	i = -1;
	while (buff[++i] != '\0')
	{
		if (buff[i] != DOLLAR)
			str = ft_strjoin_char(str, buff[i]);
		else
			str = handle_envar(buff, &i, str);
	}
	return (str);
}
