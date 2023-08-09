/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstclearback_addr.c                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:41:52 by maroy                                    */
/*   Updated: 2023/08/09 16:09:28 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_dlstclearback_addr(t_dlist **lst, void (*del)(void **))
{
	t_dlist	*then;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	while (*lst)
	{
		then = (*lst)->prev;
		if (del)
			del(&(*lst)->content);
		ft_free((void **)lst);
		(*lst) = then;
	}
}
