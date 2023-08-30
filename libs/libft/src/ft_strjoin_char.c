/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:36:42 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 20:37:11 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin_char(char *s, char c)
{
	size_t		i;
	char	*str;

	i = ft_strlen(s);
	str = (char *)malloc(i + 2);
	if (!str)
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}