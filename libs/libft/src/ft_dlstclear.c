/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstclear.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:41:39 by maroy                                    */
/*   Updated: 2023/08/09 16:09:26 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*current;
	t_dlist	*then;

	if (!lst || !*lst)
		return ;
	if (*lst)
	{
		current = (*lst)->next;
		while (current)
		{
			then = current->next;
			ft_dlstdelone(current, del);
			current = then;
		}
	}
	current = *lst;
	while (current)
	{
		then = current->prev;
		ft_dlstdelone(current, del);
		current = then;
	}
	*lst = NULL;
}
