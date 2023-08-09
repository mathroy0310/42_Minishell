/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   tokens.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/09 13:36:25 by maroy                                    */
/*   Updated: 2023/08/09 14:33:22 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

int8_t init_token(t_minishell *minishell, char *buffer)
{
    t_dlist *tokens;
    t_dlist *tmp;
    char    *tok;

    tokens = ft_malloc(sizeof(t_dlist));
    tokens->content = NULL;
    tokens->next = NULL;
    tokens->prev = NULL;
    minishell->tokens = tokens;
    tok = ft_strtok(buffer, " \t\n");
    while (tok != NULL)
    {
        printf("tok = %s\n", tok);
        tok = ft_strtok(NULL, " \t\n");
    }
}