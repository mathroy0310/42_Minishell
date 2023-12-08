/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:34 by maroy             #+#    #+#             */
/*   Updated: 2023/12/07 19:42:27 by maroy            ###   ########.fr       */
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
	if (DEBUG == 0)
		return ;
	ft_debug_printf("token->value -={ %s }=-", token->value);
	ft_debug_printf("token->type -={ %s }=-", get_token_type(token->type));
	ft_debug_printf("token->is_quoted -={ %d }=-", token->is_quoted);
	ft_debug_printf("#--------------------------------------#");
}

void debug_print_redir(t_redir *redir)
{
	if (DEBUG == 0)
		return ;
	ft_debug_printf("----------------------------------------");
	ft_debug_printf("redir->type -={ %s }=-", get_token_type(redir->type));
	ft_debug_printf("redir->filename -={ %s }=-", redir->filename);
	ft_debug_printf("redir->is_quoted -={ %d }=-", redir->is_quoted);
}

void	debug_print_cmd(t_cmd *cmd)
{
	int	i;

	if (DEBUG == 1)
	{
		i = -1;
		while (++i != cmd->nbr_cmd)
		{
			if (cmd[i].argvs)
				debug_print_tab(cmd[i].argvs);
			ft_debug_printf("cmd[%d]->nbr_cmd -={ %d }=-", i, cmd[i].nbr_cmd);
			ft_debug_printf("cmd[%d]->args_size -={ %d }=-", i, cmd[i].args_size);
			ft_debug_printf("cmd[%d]->redir_nbr -={ %d }=-", i, cmd[i].redir_nbr);
			ft_debug_printf("cmd[%d]->type -={ %s }=-", i, get_token_type(cmd[i].type));
			if (cmd[i].redir_nbr > 0)
				debug_print_redir(cmd[i].redir);
			ft_debug_printf("========================================");
		}
	}
}
