/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:56:43 by maroy             #+#    #+#             */
/*   Updated: 2023/11/07 02:40:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shlvl()
{
	char	*shlvl;
	int		shlvl_int;
	
	shlvl = get_env_var_by_key("SHLVL");
	debug_print_string("avant :", shlvl);
	shlvl_int = ft_atoi(shlvl);
	shlvl_int++;
	shlvl = ft_itoa(shlvl_int);
	debug_print_string("apres :",shlvl);
	add_var_to_env("SHLVL", shlvl);
	free(shlvl);
}