/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   tokens.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/09 13:36:25 by maroy                                    */
/*   Updated: 2023/08/16 20:56:11 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

int8_t	init_token(t_minishell *minishell, char *buffer)
{
	t_dlist	*tokens;
	t_dlist	*tmp;
	char	*tok;

	tok = NULL;
	tokens = ft_malloc(sizeof(t_dlist));
	tokens->content = NULL;
	tokens->next = NULL;
	tokens->prev = NULL;

	tok = ft_strtok(buffer, " \t\n");
	while (tok != NULL)
	{
		tmp = ft_malloc(sizeof(t_list));
		tmp->content = ft_strdup(tok);
		tmp->next = NULL;
		
		tokens->next = tmp;
		tokens = tmp;
		printf("%s\n", tokens->content);
		tok = ft_strtok(NULL, " \t\n");
	}
	minishell->tokens = tokens;
	return (OK);
}