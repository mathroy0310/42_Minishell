/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   builtins.h                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/01 14:30:21 by maroy                                    */
/*   Updated: 2023/09/20 17:07:54 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "execution.h"
# include <stdint.h>

/*
 * builtins.c *
 */

/// @brief Check if the command is a builtin
/// @param cmd The command to check
/// @return 1 if the command is a builtin, 0 otherwise
uint8_t		is_builtin(t_cmd *cmd);

/// @brief Check if the command is a builtin and execute it
/// @param cmd The command to check and execute
/// @param data The data structure
/// @return 1 if the command is a builtin, 0 otherwise
uint8_t		check_builtin(t_cmd *cmd, t_data *data);

/*
 * pwd.c *
 */

uint8_t		pwd_builtin(void);

/*
 * env.c *
 */

uint8_t		env_builtin(t_data *data);

/*
 * export.c *
 */

uint8_t		echo_builtin(char **args);

/*
 * export.c *
 */

uint8_t		export_builtin(char **args, t_data *data);
uint8_t		is_valid_env_key(char *arg);

/*
 * export_utils.c *
 */

char	**dup_env(void);

/*
 * unset.c *
 */

uint8_t	unset_builtin(char **args, t_data *data);

/*
 * cd.c *
 */
int8_t	cd_builtin(char **argv);

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
uint8_t	exit_builtin(char **args);

/*
 * utils.c *
 */

int16_t	env_count(void);
void	modify_env(char *arg, char *key);
void	sort_and_print(void);
void	free_old_env(char **env_pointer);
char	**realloc_new_env(int env_num, char *arg, char **env_pointer);
void	new_env(char *arg, char *key, t_data *data);
void	add_to_env(char *arg, t_data *data);

#endif
