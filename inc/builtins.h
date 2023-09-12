/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:30:21 by maroy             #+#    #+#             */
/*   Updated: 2023/09/11 14:37:32 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdint.h>
#include "execution.h"

/*
 * builtins.c *
 */

uint8_t is_builtin(t_cmd *cmd);
uint8_t check_builtin(t_cmd *cmd, t_data *data);

/*
 * pwd.c *
 */

uint8_t pwd_builtin(void);

/*
 * env.c *
 */

uint8_t env_builtin(t_data *data);


/*
 * export.c *
 */

uint8_t	echo_builtin(char **args);

/*
 * export.c *
 */
uint8_t export_builtin(char **args, t_data *data);
void	set_or_modify(char *arg);
void	set_new_env(char *arg);
uint8_t		is_valid_env_key(char *arg);

/*
 * unset.c *
 */

uint8_t	unset_builtin(char **args, t_data *data);

/*
 * utils.c *
 */

void modify_env(char *arg, char *key);
void sort_and_print(void);
void free_old_env(char **env_pointer);
char **realloc_new_env(int env_num, char *arg, char **env_pointer);
void new_env(char *arg, char *key, t_data *data);
void add_to_env(char *arg, t_data *data);
void print_sorted_env(char **sorted_env);
int check_only_key(char *key);

#endif