/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 10:15:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	perform_here_doc(t_redir_data *redir_cont, t_data *data, char *eof, int i)
{
	int		fd_tmp;
	(void)i;
	fd_tmp = open(redir_cont->f_name, O_WRONLY); // check returns
	if (fd_tmp == -1)
		return (error("here_doc", NULL, errno), 1);
	if (get_interactive_input(fd_tmp, &eof, data))
	{
		close(fd_tmp);
		return (error("here_doc", NULL, errno), 1);
	}
	close(fd_tmp);
	return (0);
}


static int	check_redirections(t_list *redir, t_data *data, char **eofs, int *i)
{
	t_redir_data	*redir_content;

	if (!redir)
		return (0);
	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
		{
			if (perform_here_doc(redir_content, data, eofs[*i], *i))
			{
				data->e_code = 1;
				return (1);
			}
			(*i)++;
		}
		redir = redir->next;
	}
	return (0);
}

static int	child_here_doc(t_node *tree, t_data *data, char **eofs)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		i = 0;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_redirections(cmd->redir, data, eofs, &i))
			return (free_dptr(eofs), 1);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (check_redirections(cmd->redir, data, eofs, &i))
		return (free_dptr(eofs), 1);
	return (free_dptr(eofs), 0);
}

static int	resolve_here_doc(t_node *tree, t_data *data, char **eofs)
{
	int		pid_hd;
	int		wstatus;

	pid_hd = fork();
	if (pid_hd == -1)
		return (error("fork", NULL, errno), 1);
	if (pid_hd == 0)
	{
		if (child_here_doc(tree, data, eofs))
			free_child_and_exit(data, NULL, 1);
		free_child_and_exit(data, NULL, 0);
	}
	waitpid(pid_hd, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	return (0);
}

void	here_doc(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	char	**eofs;
	(void)pipe;
	(void)cmd;
	if (!data->tree)
		return ;
	eofs = collect_eofs(tree, data);
	if (!eofs)
		return ;
	if (resolve_here_doc(tree, data, eofs))
		data->e_code = 1;
	free_dptr(eofs);
	return ;
}
