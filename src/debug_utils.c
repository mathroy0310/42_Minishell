/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:11:48 by maroy             #+#    #+#             */
/*   Updated: 2023/12/07 16:53:13 by maroy            ###   ########.fr       */
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

void debug_print_file_info(t_file *file)
{
	if (!file || DEBUG == 0)
		return ;
	ft_debug_printf("file->c_fd -={ %d }=-", file->c_fd);
	ft_debug_printf("file->c_file_path -={ %s }=-", file->c_file_path);
	ft_debug_printf("file->p_backup -={ %s }=-", file->p_backup);
	ft_debug_printf("file->readed_line =-={ %s }=-", file->readed_line);
	ft_debug_printf("----------------------------------------");
	
}