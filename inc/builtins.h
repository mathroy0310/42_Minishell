/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:30:21 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 14:38:13 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <stdint.h>

/*
* builtins.c *
*/

uint8_t	is_builtin(t_cmd *cmd);
uint8_t	check_builtin(t_cmd *cmd, t_data *data);

/*
* pwd.c *
*/

uint8_t	pwd_builtin(void);

/*
* env.c *
*/

uint8_t	env_builtin(t_data *m);


#endif