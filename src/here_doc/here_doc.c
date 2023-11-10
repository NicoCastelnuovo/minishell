/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/10 17:27:08 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_tmp_name(int n)
{
	char	*tmp_name;
	char	*digits;

	digits = ft_itoa(n); // protect
	tmp_name = ft_strjoin("tmp_", digits); // protect
	free(digits);
	return(tmp_name);
}

static int	get_interactive_input(t_redir_data *redir_content, int n)
{
	char	*line;
	char	*eof;
	int		fd_tmp;
	char	*tmp_name;

	tmp_name = get_tmp_name(n);
	fd_tmp = open(tmp_name, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR);  //ONLY THIS SESSION
	if (fd_tmp == -1)
	{
		if (errno == EEXIST)
			return (free(tmp_name), 1); // 1 means need a new name // -1 means real error
		return (-1);
	}
	line = NULL;
	eof = redir_content->file_name;
	while (1)
	{
		line = readline("> "); // protect
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		else
		{
			ft_putendl_fd(line, fd_tmp);
			if (line)
				free(line);
		}
	}
	if (line)
		free(line);
	free(redir_content->file_name);
	redir_content->file_name = ft_strdup(tmp_name);
	free(tmp_name);
	close(fd_tmp);
	return (0);
}

static void	check_here_doc(t_list *redir)
{
	t_redir_data	*redir_content;
	int				err_check;
	int				n; // n to append

	// in(<) - out(>) - EOF(<<) - EOF2(<<) ============= in(<) - out (>) - tmp_0(<<) - tmp_1(<<)
	n = 0;
	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
		{
			err_check = 1; // 1 == needs a name
			while (err_check != 0)
			{
				err_check = get_interactive_input(redir_content, n);
				if (err_check == -1)
					return ; // real error
				n++;
			}
		}
		redir = redir->next;
	}
}

void	here_doc(t_node *tree)
{
	t_pipe	*pipe;
	t_cmd	*cmd;

	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (cmd->redir)
			check_here_doc(cmd->redir);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (cmd->redir)
		check_here_doc(cmd->redir);
}
