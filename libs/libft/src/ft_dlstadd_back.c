/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstadd_back.c                                 ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 09:37:42 by maroy                                    */
/*   Updated: 2023/08/09 16:09:19 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*tmp;

	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
