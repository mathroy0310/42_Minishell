/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:34 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 20:59:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	DEBUG_print_tab(char **tab)
{
    int	i;

    i = -1;
    while (tab[++i])
        printf(BLUE "DEBUG 🐞: tab[%d] -={ %s }=-\n" DEFAULT, i, tab[i]);
}

void DEBUG_print_parser(t_parser *head) 
{
    t_parser *current = head;

    while (current != NULL) 
    {
        printf(BLUE "DEBUG 🐞: Node value -={ %s }=-\n" DEFAULT, current->curr_token->value);
        current->curr_token = current->prev_token;
    }
}

void	DEBUG_print_string(char *msg, char *arg)
{
	printf(BLUE "DEBUG 🐞: %s -={ %s }=-\n" DEFAULT, msg, arg);
}

void	DEBUG_print_decimal(char *msg, int arg)
{
	printf(BLUE "DEBUG 🐞: %s -={ %d }=-\n" DEFAULT, msg, arg);
}

void	DEBUG_print_char(char *msg, char arg)
{
	printf(BLUE "DEBUG 🐞: %s -={ %c }=-\n" DEFAULT, msg, arg);
}


void	DEBUG_print_msg(char *msg)
{
	printf(BLUE "DEBUG 🐞: -={ %s }=- \n" DEFAULT, msg);
}
