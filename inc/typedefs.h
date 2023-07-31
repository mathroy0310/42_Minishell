/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   typedefs.h                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/07/31 15:50:12 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H


typedef enum e_token_type
{
	CMD,
	SHELL_REDIRECT,
	FLAG,
	QUOTE,
	DOUBLE_QUOTE
}			t_token_type;

typedef enum e_shell_redirect
{
    PIPE,
    REDIRECT,
    APPEND,
    HEREDOC
}			t_shell_redirect;

typedef enum e_builtin
{
    ENV,
    EXPORT,
    UNSET,
    CD,
    PWD,
    EXIT
}			t_builtin;

typedef struct s_env
{
    char *value;
    struct s_env *next;
}        t_env; 

typedef struct token
{
    char *value;
    t_token_type type;
    struct t_token *next;
    struct t_token *prev;
}           t_token;

typedef struct minishell
{
    t_env *env;
    t_token token;
    signed char exit_status;
    char **path;
    char *cmd;
    char *pwd;
    char *oldpwd;
}           t_minishell;

#endif