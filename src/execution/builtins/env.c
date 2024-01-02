/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:20:11 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:10:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	env_builtin(t_data *data)
{
	int	i;

	(void)data;
	g_global->exit_status = EXIT_SUCCESS;
	i = -1;
	while (g_global->env_var[++i] != NULL)
		ft_putstr_nl(g_global->env_var[i]);
	return (OK);
}
