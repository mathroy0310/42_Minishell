/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ft_itoa.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2022/10/24 12:20:32 by maroy                                    */
/*   Updated: 2023/07/31 11:39:20 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_itoa_digitcount(int n, int *len)
{
	*len = 0;
	if (n < 0)
	{
		*len += 1;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		*len += 1;
	}
	if (n >= 0)
		*len += 1;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_itoa_digitcount(n, &len);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 9)
	{
		str[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	str[len - 1] = (n % 10) + 48;
	return (str);
}
