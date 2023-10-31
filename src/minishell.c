/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/10/28 16:29:40 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
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
		env[i] = ft_strdup(env_[i]);
	env[i] = NULL;
	return (env);
}

void	initialize(char **env, t_state *state)
{
	int	fd;

	debug_print_msg("DEBUG mode enabled 🐛");
	debug_print_msg("HISTORY_FILE: " HISTORY_FILE);
	fd = open(HISTORY_FILE, O_CREAT, S_IRUSR | S_IWUSR);
	close(fd);
	using_history();
	read_history(HISTORY_FILE);
	g_global = malloc(sizeof(t_global));
	if (g_global == NULL)
		exit(EXIT_FAILURE);
	dup_env_var(env);
	g_global->exit_status = EXIT_SUCCESS;
	g_global->pid = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
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
		debug_print_decimal("exit status", g_global->exit_status);
	}
	if (parser)
		free(parser);
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
	free(*buff);
}

t_u8	minishell_master(char **env)
{
	t_lexer	*lexer;
	char	*buff;
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	initialize(env, state);
	while (1)
	{
		buff = NULL;
		buff = readline(ANSI_COLOR_BRIGHT_YELLOW PROMPT ANSI_COLOR_RESET);
		if (!buff)
			quit_minishell(buff);
		else if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		else
		{
			lexer = NULL;
			sanitize(&buff, &lexer);
		}
		parse(lexer, state);
	}
	return (EXIT_SUCCESS);
}
