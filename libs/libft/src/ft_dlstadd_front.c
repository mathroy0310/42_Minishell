/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstadd_front.c                                ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:41:22 by maroy                                    */
/*   Updated: 2023/08/09 16:09:22 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (!alst || !new)
		return ;
	if (*alst)
	{
		(*alst)->prev = new;
		new->next = *alst;
	}
	*alst = new;
}
