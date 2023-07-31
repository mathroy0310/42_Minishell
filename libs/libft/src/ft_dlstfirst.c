/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_dlstfirst.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:42:09 by maroy                                    */
/*   Updated: 2023/07/31 11:38:25 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	if (lst)
		while (lst->previous)
			lst = lst->previous;
	return (lst);
}
