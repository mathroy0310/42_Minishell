/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   cd_utils.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/12 18:01:11 by maroy                                    */
/*   Updated: 2023/09/23 16:01:44 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	error_retrieving_cd(void)
{
	ft_putstr_fd(ANSI_COLOR_BRIGHT_RED"cd: error retrieving current directory: ", STDERR_FILENO);
	ft_putstr_fd(ANSI_COLOR_BRIGHT_RED"getcwd: cannot access parent directories: ", STDERR_FILENO);
	printf("%s", strerror(errno));
	ft_putendl_fd(ANSI_COLOR_RESET, STDERR_FILENO);
}

char	*add_char_to_word(char *word, char c)
{
	char	*save_word;
	int		new_word_len;

	if (!word)
	{
		word = (char *)ft_memalloc(sizeof(char) * 2);
		if (!word)
			return (NULL);
		word[0] = c;
		word[1] = '\0';
		return (word);
	}
	new_word_len = ft_strlen(word) + 2;
	save_word = word;
	word = (char *)ft_memalloc(sizeof(char) * new_word_len);
	if (!word)
		return (NULL);
	ft_memcpy(word, save_word, ft_strlen(save_word));
	word[ft_strlen(save_word)] = c;
	return (word);
}

char	*get_pwd(void)
{
	char	*new_pwd;

	new_pwd = (char *)malloc(sizeof(char) * PATH_MAX + 1);
	if (!new_pwd)
		return (NULL);
	ft_bzero(new_pwd, PATH_MAX + 1);
	if (getcwd(new_pwd, sizeof(char) * PATH_MAX) == NULL)
	{
		free(new_pwd);
		return (NULL);
	}
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
	g_global->exit_status = 1;
	debug_print_msg("dans error_path");
	printf(ANSI_COLOR_BRIGHT_RED ERR_PROMPT "%s: %s: %s",
		cmd, path, strerror(errnum));
	printf("\n");
	return (EXIT_FAILURE);
}
