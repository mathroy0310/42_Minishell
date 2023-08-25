/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/23 16:35:22 by maroy                                    */
/*   Updated: 2023/08/24 20:50:15 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void parse_double_redir(char *src, char **dest, int *i, int *nb_tokens)
{
    dest[*nb_tokens] = malloc(sizeof(char) * (3));
    ft_strlcpy(dest[*nb_tokens], ">>", 3);
    *i += 2;
    dest[*nb_tokens] = ft_strtok(&src[*i], " ");
    *i += ft_strlen(dest[(*nb_tokens)++]) - 1;
}

static void parse_single_token(char *src, char **dest, int *i, int *nb_tokens)
{
    dest[*nb_tokens] = malloc(sizeof(char) * (2));
    ft_strlcpy(dest[(*nb_tokens)++], &src[(*i)++], 2);
    dest[*nb_tokens] = ft_strtok(&src[*i], " ");
    *i += ft_strlen(dest[(*nb_tokens)++]) - 1;
}

static void parse_inner_tokens(char *src, char **dest, int *i, int *nb_tokens)
{
    int size;
    int start;

    size = ft_strchr(&src[*i], ' ') - &src[*i];
    if (size < 0 || size > BUFFER_SIZE)
        size = ft_strlen(&src[*i]);
    start = *i;
    while (size--)
    {
        if (src[*i] == '>' || src[*i] == '<' || src[*i] == '|')
        {
            if (*i != start)
                dest[(*nb_tokens)++] = ft_strtok(&src[start], &src[*i]);
            if (src[*i + 1] && src[*i + 1] == '>' && src[*i + 2] != ' ')
                return (parse_double_redir(src, dest, i, nb_tokens));
            return (parse_single_token(src, dest, i, nb_tokens)); 
        }
        *i += 1;        
    }
    *i = start;
    dest[*nb_tokens] = ft_strtok(&src[*i], " ");
    *i += ft_strlen(dest[(*nb_tokens)++]) - 1;
    
}      

static void _parse(char *src, char **dest, int *i, int *nb_tokens)
{
    int size;
    char *end;

    if (src[*i + 1] && (src[*i] == '\'' || src[*i] == '\"') && (ft_strchr(&src[*i + 1], '\'') || ft_strchr(&src[*i + 1], '\"')))
    {
        end = ft_strchr(&src[*i + 1], src[*i]);
        size = end - &src[*i] + 2;
        dest[*nb_tokens] = (char *)ft_calloc(size, sizeof(char));
        ft_strlcpy(dest[*nb_tokens++], &src[*i], size);
        i += size - 2;
    }
    else
    {
        parse_inner_tokens(src, dest, i, nb_tokens);
    }
}

void parse(char *src, char **dest)
{
    int i;
    int nb_tokens;

    i = -1;
    nb_tokens = 0;
    while (src[++i])
    {
        while (src[i] == ' ' || src[i] == '\t' || src[i] == '\a' || src[i] == '\r' || src[i] == '\v' || src[i] == '\f')
            i++;
        _parse(src, dest, &i, &nb_tokens);
    }
    dest[nb_tokens] = NULL;
    while (dest[++nb_tokens])
        free(dest[nb_tokens]);
    
}