/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:34:10 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 16:42:45 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	export_builtin(char **args)
{
    g_global->exit_status = 0;
	if (!args[1])
	{
		sort_and_print();
		return (OK);
	}
	return (OK);
}