/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:39:22 by maroy             #+#    #+#             */
/*   Updated: 2023/12/11 18:11:00 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_global(void)
{
	ft_free_tab(g_global->env_var);
	ft_free(g_global);
}

void	free_state(t_state *state)
{
	ft_free_tab(state->path);
	ft_free_tab(state->env_);
	ft_free(state);
}
