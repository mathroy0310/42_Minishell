/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:30:21 by maroy             #+#    #+#             */
/*   Updated: 2023/11/14 01:48:18 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "execution.h"
# include <stdint.h>

/*
 * builtins.c *
 */

t_u8	is_builtin(t_cmd *cmd);

t_u8	check_builtin(t_cmd *cmd, t_data *data);

/*
 * pwd.c *
 */

t_u8	pwd_builtin(void);

/*
 * env.c *
 */

t_u8	env_builtin(t_data *data);

/*
 * export.c *
 */

t_u8	echo_builtin(char **args);

/*
 * export.c *
 */

t_u8	export_builtin(char **args, t_data *data);
t_u8	is_valid_env_key(char *arg);

/*
 * export_utils.c *
 */

char	**dup_env(void);

/*
 * unset.c *
 */

t_u8	unset_builtin(char **args, t_data *data);

/*
 * cd.c *
 */
int		add_var_to_env(char *key, char *new_path);
t_u8	cd_builtin(char **argv);

/*
 * cd_utils.c *
 */
char	*get_pwd(void);
void	error_retrieving_cd(void);
char	*return_value(const char *s, int c);
char	*add_char_to_word(char *word, char c);
int		error_path(const char *cmd, const char *path, int errnum);
/*
 * exit.c *
 */
t_u8	exit_builtin(char **args);

/*
 * utils.c *
 */

int		env_count(void);
void	modify_env(char *arg, char *key);
void	sort_and_print(void);
void	free_old_env(char **env_pointer);
char	**realloc_new_env(int env_num, char *arg, char **env_pointer);
void	new_env(char *arg, char *key, t_data *data);
void	add_to_env(char *arg, t_data *data);

#endif
