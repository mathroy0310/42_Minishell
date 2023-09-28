/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   here_doc.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/19 22:47:03 by maroy                                    */
/*   Updated: 2023/09/27 14:43:57 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"


char	*here_doc_helper(char *buf, char *dst, char *filename, int is_quoted)
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
	dst = ft_strjoin_free(dst, envar_here_doc(buf, is_quoted));
	free(buf);
	return (dst);
}


static int	random_file_name(t_data *data)
{
	static int	file_nbr = 0;
	char		*name;
	char		*itoa_nbr;
	int			fd;

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
		exit (g_global->exit_status);
	}
	return (fd);
}

void	parse_here_doc(t_redir *redir, t_data *data)
{
	char	*buf;
	char	*dst;
	char	*temp;
	int		fd;
	int		empty;

	empty = 0;
	fd = random_file_name(data);
	dst = ft_strdup("");
	while (1)
	{
		empty++;
		data->redir->here_doc = 1;
		buf = readline("> ");
		temp = dst;
		dst = here_doc_helper(buf, dst, redir->filename, redir->is_quoted);
		if (!dst)
			break ;
	}
	if (empty != 1)
		ft_putendl_fd(temp, fd);
	free(dst);
	free(temp);
	close (fd);
}
