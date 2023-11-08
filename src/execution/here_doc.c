/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   here_doc.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/19 22:47:03 by maroy                                    */
/*   Updated: 2023/11/08 14:19:25 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc_helper(char *buf, char *dst, char *filename, bool is_quoted)
{
	char	*temp;

	if (!ft_strcmp(buf, filename))
	{
		free(buf);
		return (NULL);
	}
	if (ft_strcmp(dst, "\0"))
	{
		temp = dst;
		dst = ft_strjoin(dst, "\n");
		free(temp);
	}
	if (!buf)
		return (dst);
	dst = ft_strjoin_free(dst, envar_here_doc(buf, is_quoted));
	free(buf);
	return (dst);
}

static int	random_file_name(t_data *data)
{
	static int	file_nbr;
	char		*name;
	char		*itoa_nbr;
	int			fd;

	file_nbr = 0;
	file_nbr++;
	name = NULL;
	itoa_nbr = ft_itoa(file_nbr);
	name = ft_strjoin(HERE_DOC_FILE, itoa_nbr);
	free(itoa_nbr);
	data->redir->filename = name;
	fd = open(data->redir->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		check_valid_fd(data, data->redir->filename, fd);
		exit(g_global->exit_status);
	}
	return (fd);
}

void	parse_here_doc(t_redir *redir, t_data *data)
{
	char	*buf;
	char	*dst;
	int		fd;
	int		empty;
	pid_t	child_pid;

	empty = 0;
	fd = random_file_name(data);
	dst = ft_strdup("");
	g_global->pid = 0;
	child_pid = fork();
	if (child_pid < 0)
		fork_failed();
	else if (child_pid == 0)
	{
		signal(SIGINT, sigint_here_doc_handler);
		while (1)
		{
			empty++;
			data->redir->is_here_doc = true;
			buf = readline("> ");
			if (!buf)
				break ;
			dst = here_doc_helper(buf, dst, redir->filename, redir->is_quoted);
			debug_print_string("dst ->", dst);
			if (!dst)
				break ;
		}
	}
	signals_init();
	if (empty != 1)
		ft_putstr_fdnl(fd, dst);
	free(dst);
	close(fd);
}
