/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:56:43 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:06:56 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	*g_global;

static char	**get_env_(char **env_)
{
	char	**env;
	int		i;

	i = -1;
	env = (char **)ft_malloc(sizeof(char *) * ((size_t)ft_tablen(env_) + 1));
	while (++i < ft_tablen(env_))
	{
		env[i] = ft_strdup(env_[i]);
	}
	env[i] = NULL;
	return (env);
}

void	mini_init(char **env, t_state *state)
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

void	quit_minishell(char *buff)
{
	ft_putstr_nl("exit");
	ft_free(buff);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_state	*state;

	(void)argv;
	(void)argc;
	state = (t_state *)malloc(sizeof(t_state));
	mini_init(envp, state);
	ret = minishell_master(state);
	free_state(state);
	ft_free_tab(g_global->env_var);
	free(g_global);
	return (ret);
}
