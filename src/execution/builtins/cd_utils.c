
/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   cd_utils.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/12 18:01:11 by maroy                                    */
/*   Updated: 2023/10/28 16:35:53 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"
#define CD_ERR "cd: error retrieving current directory:\
	getcwd: cannot access parent directories: "

void	error_retrieving_cd(void)
{
	ft_putstr_err(FT_RED CD_ERR);
	ft_printf("%s", strerror(errno));
	ft_putstr_errnl(FT_COLOR_RESET);
}

char	*add_char_to_word(char *word, char c)
{
	char	*save_word;
	int		new_word_len;

	if (!word)
	{
		word = (char *)ft_malloc(sizeof(char) * 2);
		word[0] = c;
		word[1] = '\0';
		return (word);
	}
	new_word_len = ft_strlen(word) + 2;
	save_word = word;
	word = (char *)ft_malloc(sizeof(char) * new_word_len);
	ft_memcpy(word, save_word, ft_strlen(save_word));
	word[ft_strlen(save_word)] = c;
	return (word);
}

char	*get_pwd(void)
{
	char	*new_pwd;

	new_pwd = (char *)malloc(sizeof(char) * PATH_MAX + 1);
	ft_bzero(new_pwd, PATH_MAX + 1);
	if (!getcwd(new_pwd, sizeof(char) * PATH_MAX))
		return (ft_free(new_pwd), NULL);
	return (new_pwd);
}

char	*return_value(const char *s, int c)
{
	char	*str;
	char	val;
	int		i;

	i = ft_strlen(s);
	str = (char *)s;
	val = (char)c;
	while (i >= 0)
	{
		if (*str == val)
		{
			str++;
			return (str);
		}
		str++;
		i--;
	}
	return (NULL);
}

int	error_path(const char *cmd, const char *path, int errnum)
{
	g_global->exit_status = EXIT_FAILURE;
	ft_printf(FT_RED ERR_PROMPT "%s: %s: %s \n", cmd, path, strerror(errnum));
	ft_printf(FT_COLOR_RESET);
	return (g_global->exit_status);
}