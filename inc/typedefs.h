/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   typedefs.h                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/08/16 19:53:10 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef enum e_token_type
{
	CMD,
	FLAG,
	PIPE,
	REDIRECT,
	APPEND,
	QUOTE,
	DOUBLE_QUOTE,
	HEREDOC,
	END
}			t_token_type;

typedef struct minishell
{
	t_list	*env;
	t_dlist	*tokens;
	int		exit_status;
	char	**envp;
	char	*cmd;
	int		fd_in;
	int		fd_out;
	char	*pwd;
	char	*oldpwd;
}			t_minishell;

#endif