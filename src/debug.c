/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:34 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 16:01:32 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_tab(char **tab)
{
	int	i;

	if (DEBUG == 1)
	{
		i = -1;
		while (tab[++i])
			ft_debug_printf("tab[%d] -={ %s }=-", i, tab[i]);
	}
}
void	debug_print_token(t_token *token)
{
	if (DEBUG == 1)
	{
		ft_debug_printf("token->value -={ %s }=-", token->value);
		ft_debug_printf("token->type -={ %s }=-", get_token_type(token->type));
		ft_debug_printf("token->is_quoted -={ %d }=-", token->is_quoted);
		ft_debug_printf("----------------------------------------");
	}
}


void	debug_print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	if (DEBUG == 1)
	{
		i = -1;
		while (++i != cmd->nbr_cmd)
		{
			j = -1;
			if (cmd[i].argvs)
				debug_print_tab(cmd[i].argvs);
			ft_debug_printf("cmd[%d]->nbr_cmd -={ %d }=-", i, cmd[i].nbr_cmd);
			ft_debug_printf("cmd[%d]->args_size -={ %d }=-", i, cmd[i].args_size);
			ft_debug_printf("cmd[%d]->redir_nbr -={ %d }=-", i, cmd[i].redir_nbr);
			ft_debug_printf("----------------------------------------");
		}
	}
}
