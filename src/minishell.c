/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:56:43 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 22:22:15 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static char	**get_env_(char **env_)
{
	char	**env;
	int		i;

	i = -1;
	env = (char **)malloc(sizeof(char *) * (ft_tablen(env_) + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	while (++i < ft_tablen(env_))
	{
		env[i] = ft_strdup(env_[i]);
	}
	env[i] = NULL;
	return (env);
}

void	initialize(char **env, t_state *state)
{
	if (DEBUG)
	{
		ft_debug_printf("DEBUG mode enabled 🐛");
		ft_debug_printf("HISTORY_FILE: %s", HISTORY_FILE);
	}
	use_history();
	g_global = ft_malloc(sizeof(t_global));
	dup_env_var(env);
	g_global->has_exited = FALSE;
	g_global->exit_status = EXIT_SUCCESS;
	g_global->pid = 1;
	signals_init();
	state->env_ = get_env_(env);
	state->path = NULL;
}

static void	parse(t_lexer *lexer, t_state *state)
{
	t_cmd		*cmd;
	t_ast		*ast;
	t_parser	*parser;

	parser = init_parser(lexer);
	if (parser)
	{
		// debug_print_parser(parser);
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
		(*lexer)->bufsize = ft_strlen((*lexer)->buffer);
	}
	ft_free(*buff);
}

t_u8	minishell_master(char **env)
{
	t_lexer	*lexer;
	char	*buff;
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	initialize(env, state);
	while (!g_global->has_exited)
	{
		buff = NULL;
		buff = readline(FT_BYEL PROMPT FT_COLOR_RESET);
		buff = check_line(buff);
		if (ft_strequal(buff, "break"))
			break ;
		else if (ft_strequal(buff, "continue"))
			continue ;
		else
		{
			lexer = NULL;
			sanitize(&buff, &lexer);
		}
		parse(lexer, state);
	}
	free_state(state);
	return (g_global->exit_status);
}
