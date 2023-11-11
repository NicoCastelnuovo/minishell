/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/11 11:58:12 by ncasteln         ###   ########.fr       */
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

static void	write_into_tmp_file(int fd_tmp, char *eof, t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> "); // protect
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			// chceck if need to insert a newline
			break ;
		}
		else
		{
			if (data)
				line = expand(line, data->env, data->e_code);
			ft_putendl_fd(line, fd_tmp);
			if (line)
				free(line);
		}
	}
	if (line)
		free(line);
}

static char	*trim_quotes(char *old_str)
{
	char	*new;
	int		old_len;
	int		i;
	int		j;

	old_len = ft_strlen(old_str);
	new = ft_calloc(ft_strlen(old_str) - 1, sizeof(char)); //protect
	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (i == 0 || i == old_len - 1)
			i++;
		else
		{
			new[j] = old_str[i];
			i++;
			j++;
		}
	}
	return (new);
}

static int	get_interactive_input(t_redir_data *redir_content, int n, t_data *data)
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
	if (eof[0] == '\'' || eof[0] == '\"')
	{
		eof = trim_quotes(redir_content->file_name);
		write_into_tmp_file(fd_tmp, eof, NULL);
	}
	else
		write_into_tmp_file(fd_tmp, eof, data);
	free(redir_content->file_name);
	redir_content->file_name = ft_strdup(tmp_name);
	free(tmp_name);
	close(fd_tmp);
	return (0);
}

static void	check_here_doc(t_list *redir, t_data *data)
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
				err_check = get_interactive_input(redir_content, n, data);
				if (err_check == -1)
				{
					// real error
					// need to clean up
					return ;
				}
				n++;
			}
		}
		redir = redir->next;
	}
}

void	here_doc(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;

	// add available history ????
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (cmd->redir)
			check_here_doc(cmd->redir, data);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (cmd->redir)
		check_here_doc(cmd->redir, data);
}
