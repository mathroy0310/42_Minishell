/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:19:35 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 21:18:24 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_str_from_char(char *str, char c, t_bool flag)
{
	char	*str2;
	int		ret;

	str2 = ft_strchr(str, c);
	if (!str2 && flag == FALSE)
		return (-1);
	else if (!str2 && flag == TRUE)
		return (0);
	else
		ret = (int)(str2 - str);
	return (ret);
}
