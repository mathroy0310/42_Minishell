/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:20:11 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 20:33:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	env_builtin(t_data *data)
{
	int i;

	i = -1;
	g_global->exit_status = EXIT_SUCCESS;
	i = -1;
	while (data->state->env_[++i] != NULL)
		ft_putstr_nl(data->state->env_[i]);
	return (OK);
}