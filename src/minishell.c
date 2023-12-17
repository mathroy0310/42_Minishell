/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:56:43 by maroy             #+#    #+#             */
/*   Updated: 2023/12/17 01:39:38 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse(t_lexer *lexer, t_state *state)
{
	t_cmd		*cmd;
	t_ast		*ast;
	t_parser	*parser;

	parser = init_parser(lexer);
	if (parser)
	{
		ast = parse_pipe(parser);
		if (ast)
		{
			cmd = parse_pipeline_to_cmd(ast);
			if (cmd)
			{
				debug_print_cmd(cmd);
				execution(cmd, state);
				if (cmd)
					free_cmd(cmd);
			}
		}
		if (DEBUG)
			ft_debug_printf("exit status %d", g_global->exit_status);
	}
}

static void	sanitize(char **buff, t_lexer **lexer)
{
	add_history(*buff);
	append_history(1, HISTORY_FILE);
	if (!is_white_space(*buff))
	{
		*lexer = init_lexer(*lexer);
		(*lexer)->buffer = ft_strdup(*buff);
		(*lexer)->bufsize = (int)ft_strlen((*lexer)->buffer);
	}
	ft_free(*buff);
}

t_u8	minishell_master(t_state *state)
{
	t_lexer	*lexer;
	char	*buff;
	
	while (!g_global->has_exited)
	{
		buff = NULL;
		buff = readline(FT_BYEL PROMPT FT_COLOR_RESET);
		if (!buff)
		{
			quit_minishell(buff);
			break ;
		}
		else if (buff[0] == '\0')
		{
			ft_free(buff);
			continue ;
		}
		else
		{
			lexer = NULL;
			sanitize(&buff, &lexer);
		}
		parse(lexer, state);
	}
	return (g_global->exit_status);
}
