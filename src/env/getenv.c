/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:14:52 by maroy             #+#    #+#             */
/*   Updated: 2023/08/28 14:58:26 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	are_equal(char *one, char *other)
{
	return (ft_memcmp(other, one, ft_strlen(one)));
}

static t_list	*lst_find(t_list **list, char *key)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (are_equal(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*getenv_value(t_list *envp[], char *key)
{
	t_list			*tmp;

	tmp = lst_find(envp, key);
	if (tmp)
		return (tmp->value);
	return (NULL);
}