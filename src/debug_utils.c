/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:11:48 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 14:12:30 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_type(t_token_type type)
{
		if (type == pip)
			return ("pip");
		else if (type == great)
			return ("great");
		else if (type == greater)
			return ("greater");
		else if (type == less)
			return ("less");
		else if (type == here_doc)
			return ("here_doc");
		else if (type == id)
			return ("id");
		else if (type == illegal)
			return ("illegal");
		else if (type == eof)
			return ("eof");
		else
			return ("unknown");
}