/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:17:10 by maroy             #+#    #+#             */
/*   Updated: 2023/08/28 15:01:09 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "minishell.h"

/*
 * -- Prototypes --
 */

//DEBUG
void    DEBUG_print_token_type(t_token *tokens);
void    DEBUG_print_tab(char **tab);
void    DEBUG_print_msg(char *msg);
void    DEBUG_print_arg(char *msg, char *arg);

int	handle_execute(t_minishell *minishell);

//expand
void	expand_args(t_minishell *minishell);

//parsing
void parsing(char *src, char **dest);

void parse_tokens(t_token *tokens);
// Init
t_minishell	*init(char **envp);

t_minishell	*init_env(char *envp[]);

//files
int8_t	handle_file(char *filename, int open_flag);

// Builtins
int8_t	exec_env(t_list *env);
int8_t	exec_pwd(void);

//env
char	*getenv_value(t_list *envp[], char *key);

// Signal
void	sig_interrupt(int sig);
int 	*get_signal_triggered_status(void);
void	handle_heredoc_signal(int signal_number);

int8_t	handle_tokens(char *str, t_minishell *minishell);

// Readline
int8_t	take_input(char *buffer, t_minishell *minishell);

// valid
int8_t	using_valid_characters(char *buff, t_minishell *minishell);

// error
uint8_t	print_token_error(char c);
uint8_t	print_msg_error(char *msg);
uint8_t	print_arg_error(char *msg, char *arg);
// free
void	destroy_program(t_minishell *minishell);

#endif