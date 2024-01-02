/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 01:20:41 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 02:50:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_here_doc(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		if (cmd[i].redir->type == here_doc)
			data->redir->is_here_doc = TRUE;
	}
	if (data->redir->is_here_doc == FALSE)
		return ;
}
static char	*find_delimiter(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		if (cmd[i].redir->type == here_doc)
			return (cmd[i].redir->filename);
	}
	return (NULL);
}

int	random_name_fd(t_data *data)
{
	static int	i = 0;
	int			fd;

	data->redir->filename = ft_strjoin_free(ft_strdup("./.tmp/file"),
			ft_itoa(i++));
	fd = open(data->redir->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (DEBUG)
		ft_debug_printf("filename-={ %s }, new fd-={ %d }=-",
			data->redir->filename, fd);
	if (fd < 0)
	{
		ft_putstr_err(FT_RED ERR_PROMPT "Failed To create the temp heredoc file");
		ft_putstr_errnl(FT_COLOR_RESET);
		g_global->exit_status = EXIT_FAILURE;
	}
	ft_free(data->redir->filename);
	return (fd);
}

static void	here_doc_eof(int line_nbr, char *delim)
{
	ft_putstr_err(FT_RED ERR_PROMPT "warning:  here-document at line ");
	ft_puti_err(line_nbr);
	ft_putstr_err(" delimited by end-of-file (wanted `");
	ft_putstr_err(delim);
	ft_putstr_errnl("')");
	ft_putstr(FT_COLOR_RESET);
}

char *here_doc_helper(char *buff, char *output, char* filename, t_bool is_quoted)
{
	
}


t_u8	execute_here_doc(t_cmd *cmd, t_data *data)
{
	char		*delim;
	int			fd;
	int			line_nbr;
	char	*buff;
	pid_t		pid;

	line_nbr = 0;
	if (DEBUG)
		ft_debug_printf("execute_here_doc");
	fd = random_name_fd(data);
	if (fd < 0)
		return (KO);
	delim = find_delimiter(cmd);
	if (delim == NULL)
		return (KO);
	pid = fork();
	if (pid == 0)
	{
		while (TRUE)
		{
			line_nbr++;
			buff = readline("> ");
			if (!buff)
			{
				here_doc_eof(line_nbr, delim);
				break ;
			}
			if (!ft_strcmp(buff, delim))
			{
				ft_free(buff);
				break ;
			}
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		return (KO);
	ft_close(fd);
	return (OK);
}
