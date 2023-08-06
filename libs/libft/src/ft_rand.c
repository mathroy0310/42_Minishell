/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_rand.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 15:56:10 by maroy                                    */
/*   Updated: 2023/08/01 15:56:44 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_rand(int min, int max)
{
	int	rand;
	int	diff;
	int	div;

	diff = max - min;
	div = RAND_MAX / diff;
	rand = min + (int)(random() / div);
	while (rand > max)
		rand = min + (int)(random() / div);
	return (rand);
}
