/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstpop_back.c                                 ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:42:47 by maroy                                    */
/*   Updated: 2023/07/31 12:22:19 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_dlstpop_back(t_dlist **head, void (*del)(void*))
{
	t_dlist	**current;
	t_dlist	*then;

	if (!head || !del || !*head)
		return ;
	current = head;
	while (*current)
	{
		then = (*current)->next;
		if (!then)
		{
			ft_dlstdelone(*current, del);
			*current = NULL;
			return ;
		}
		current = &(*current)->next;
	}
}
