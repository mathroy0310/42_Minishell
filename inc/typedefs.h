/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   typedefs.h                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/08/21 16:06:35 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef enum e_token_type
{
	CMD,
    ARG,
	FLAG,
	PIPE,
	REDIRECT,
    QUOTED_STRING,
    ENV_VAR,
	END
}			t_token_type;

typedef struct s_token
{
	char			    *content;
	struct s_token	    *next;
	struct s_token	    *prev;
    enum e_token_type    type;
}					t_token;


typedef struct minishell
{
	t_list	*env;
	t_token	*tokens;
	int		exit_status;
	char	**envp;
	char	*cmd;
	int		fd_in;
	int		fd_out;
	char	*pwd;
	char	*oldpwd;
}			t_minishell;

#endif