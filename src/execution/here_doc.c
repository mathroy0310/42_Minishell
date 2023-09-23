/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   here_doc.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/19 22:47:03 by maroy                                    */
/*   Updated: 2023/09/23 14:30:49 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static char	*herdoc_helper(char *buff, char *output, char *filename, int is_quoted)
{
	char	*temp;

	if (!ft_strcmp(buff, filename))
	{
		free(buff);
		return (NULL);
	}
	if (ft_strcmp(output, "\0"))
	{
		temp = output;
		output = ft_strjoin(output, "\n");
		free(temp);
	}
	output = ft_strjoin_free(output, envar_here_doc(buff, is_quoted));
	free(buff);
	return (output);
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
	char	*buff;
	char	*output;
	char	*temp;
	int		fd;
	int		empty;

	empty = 0;
	fd = random_file_name(data);
	output = ft_strdup("");
	while (1)
	{
		empty++;
		data->redir->here_doc = 1;
		buff = readline("> ");
		temp = output;
		output = herdoc_helper(buff, output, redir->filename, redir->is_quoted);
		if (!output)
			break ;
	}
	if (empty != 1)
		ft_putendl_fd(temp, fd);
	free(output);
	free(temp);
	close (fd);
}
