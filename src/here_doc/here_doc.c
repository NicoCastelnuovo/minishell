/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/10 15:21:51 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_new_name(char *name)
{
	char	*digits;
	int		i;

	digits = ft_calloc(5, sizeof(char)); // protect
	i = 0;
	while (!ft_isdigit(name[i]))
		i++;
	while (name[i])
	{
		digits[i] = name[i];
		i++;
	}
}

static int	create_tmp_file(void)
{
	int		fd_tmp;
	char	*name;

	name = ft_strdup("tmp_0000");
	fd_tmp = open(name, O_CREAT | O_EXCL | O_RDWR, S_IRUSR); // change options
	while (fd_tmp == -1 && errno == EEXIST)
	{
		ft_printf("\033[0;34m ********* NEW NAME REQUIRED ********* \033[0;37m\n");
		name = create_new_name(name);
		fd_tmp = open(name, O_CREAT | O_EXCL | O_RDWR, S_IRUSR); // change options
		if (fd_tmp == -1 && errno != EEXIST)
		{
			ft_printf("\033[0;31m ********* ERROR OPENING FILE ********* \033[0;37m\n");
			return ;
		}
	}
	return (fd_tmp);
}

static void	get_input(t_redir_data *redir_content)
{
	char	*line;
	char	*eof;
	int		fd_tmp;

	fd_tmp = create_tmp_file();

	fd_tmp = open("tmp", O_CREAT | O_EXCL | O_RDWR, S_IRUSR); // change options
	while (fd_tmp == -1 && errno == EEXIST)
	{
		// new name
		ft_printf("\033[0;34m ********* NEW NAME REQUIRED ********* \033[0;37m\n");
		char	*new_name = "tmp_2";
		fd_tmp = open(new_name, O_CREAT | O_EXCL | O_RDWR, S_IRUSR); // change options
		if (fd_tmp == -1 && errno != EEXIST)
		{
			ft_printf("\033[0;31m ********* ERROR OPENING FILE ********* \033[0;37m\n");
			return ;
		}
	}
	line = NULL;
	eof = redir_content->file_name;
	while (1)
	{
		if (line)
			free(line);
		line = readline("> "); // protect
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		else
			ft_putendl_fd(line, fd_tmp);
	}
	ft_printf("DONE\n");
	exit(1);
}

static void	check_here_doc(t_list *redir)
{
	t_redir_data	*redir_content;

	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
			get_input(redir_content);
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
	// check tree
	cmd = (t_cmd *)tree->content;
	if (cmd->redir)
		check_here_doc(cmd->redir);
}
