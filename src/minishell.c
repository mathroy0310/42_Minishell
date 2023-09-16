/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/09/16 18:46:05 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	env[i] = 0;
	return (env);
}

void	initialize(int argc, char **argv, char **env, t_state *state)
{
	(void)argc;
	(void)argv;
	debug_print_msg("DEBUG mode enabled 🐛");
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

void	quit_minishell(char *buff)
{
	char	*up;
	char	*ri;

	up = tgetstr("up", NULL);
	ri = tgetstr("RI", NULL);
	tputs(ri, 1, putchar);
	tputs(up, 1, putchar);
	ft_putendl_fd("exit", STDOUT_FILENO);
	free(buff);
	exit(g_global->exit_status);
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
			cmd = visitor(ast);
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
		(*lexer) = init_lexer(*lexer);
		(*lexer)->buffer = ft_strdup(*buff);
		(*lexer)->bufsize = ft_strlen((*lexer)->buffer);
	}
	free(*buff);
}

uint8_t	minishell_master(int argc, char **argv, char **env)
{
	t_lexer	*lexer;
	char	*buff;
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	initialize(argc, argv, env, state);
	while (1)
	{
		buff = NULL;
		buff = readline(YELLOW PROMPT DEFAULT);
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
