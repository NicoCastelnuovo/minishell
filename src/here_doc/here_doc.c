/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 07:13:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_tmp_name(int n)
{
	char	*tmp_name; // remember to throw an error in case of >".tmp_" something
	char	*digits;

	digits = ft_itoa(n); // protect
	tmp_name = ft_strjoin(".tmp_", digits); // protect
	free(digits);
	return(tmp_name);
}

/*
	@param data: data is passed only in case the expansion has to be performed.
	Otherwise NULL is passed, and expansion is skipped.
*/
static int	write_into_tmp_file(int fd_tmp, char *eof, t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof) == 0)
			break ;
		else
		{
			if (data && ft_strchr(line, '$'))
			{
				line = expand(line, data->env, data->e_code);
				if (!line)
					return (error("here_doc", "expand", CE_HERE_DOC), 1);
			}
			ft_putendl_fd(line, fd_tmp);
			if (line)
				free(line);
		}
	}
	if (line)
		free(line);
	return (0);
}

/*
	There are two kinds of interactive input. If the eof is surrounded by
	any kind of wuotes, the expansion is not performed.
*/
static int	get_interactive_input(int fd_tmp, char **eof, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (*eof[0] == '\'' || *eof[0] == '\"')
	{
		tmp = *eof;
		*eof = ft_strtrim(*eof, "'\"");
		free(tmp);
		if (!*eof)
			return (1);
		if (write_into_tmp_file(fd_tmp, *eof, NULL))
			return (1);
	}
	else
	{
		if (write_into_tmp_file(fd_tmp, *eof, data)) // no quotes
			return (1);
	}
	return (0);
}

static int	perform_here_doc(t_redir_data *redir_content, t_data *data)
{
	int		fd_tmp;
	char	*tmp_name;
	char	*eof;
	int		n;

	n = 0;
	fd_tmp = -1;
	tmp_name = NULL;
	while (fd_tmp == -1)
	{
		if (n == INT_MAX)
			return (error("here_doc", "INT_MAX", CE_HERE_DOC), -1);
		tmp_name = get_tmp_name(n);
		if (!tmp_name)
			return (error("here_doc", tmp_name, CE_HERE_DOC), -1);
		fd_tmp = open(tmp_name, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd_tmp == -1)
		{
			if (tmp_name)
				free(tmp_name);
			if (errno == EEXIST)
				n++;
			else
				return (error("here_doc", "open", errno), -1);
		}
	}
	eof = ft_strdup(redir_content->file_name);
	free(redir_content->file_name);
	redir_content->file_name = tmp_name;
	if (get_interactive_input(fd_tmp, &eof, data))
	{
		free(eof);
		close(fd_tmp);
		return (1);
	}
	free(eof);
	close(fd_tmp);
	return (0);
}

static int	check_here_doc(t_list *redir, t_data *data)
{
	t_redir_data	*redir_content;

	if (!redir)
		return (0);
	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
		{
			if (perform_here_doc(redir_content, data))
			{
				data->e_code = 1;
				return (1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

void	here_doc(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;

	if (data->e_code || !data->tree)
		return ;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_here_doc(cmd->redir, data))
			return ;
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	check_here_doc(cmd->redir, data);
}
