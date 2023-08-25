/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   init.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/08/24 18:42:37 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*ft_lstnew2(char *content)
{
	t_list	*element;
	char	**splitted;

	splitted = ft_split(content, '=');
	element = (t_list *)malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	element->key = ft_strdup(splitted[0]);
	if (splitted[1])
		element->value = ft_strdup(splitted[1]);
	else
		element->value = NULL;
	element->content = content;
	element->next = NULL;
	ft_free_tab(splitted);
	return (element);
}

t_list	**to_linked_list(char **envp)
{
	t_list	**list;
	int		i;

	i = -1;
	list = (t_list **)malloc(sizeof(t_list *));
	*list = NULL;
	while (envp[++i])
		ft_lstpush(list, ft_lstnew2(envp[i]));
	return (list);
}

t_minishell	*init_env(char *envp[])
{
	t_minishell	*minishell;

	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	minishell->exit_status = 0;
	minishell->env = to_linked_list(envp);
	return (minishell);
}

t_minishell	*init(char **envp)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	//macos
	//term.c_lflag &= ~(ECHOCTL);
	//linux 
	term.c_lflag &= ~(ECHONL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (0);
	return (init_env(envp));
}
