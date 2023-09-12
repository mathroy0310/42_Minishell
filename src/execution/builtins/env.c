/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:20:11 by maroy             #+#    #+#             */
/*   Updated: 2023/09/11 13:53:02 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	env_builtin(t_data *data)
{
	int	i;

	i = -1;
	g_global->exit_status = 0;
	i = -1;
	while (data->state->env_[++i] != NULL)
		ft_putendl_fd(data->state->env_[i], STDOUT_FILENO);
	return (OK);
}
