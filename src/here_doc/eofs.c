/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eofs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:13:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 17:53:29 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int store_eofs_single_block(t_list *redir, t_data *data, char **eofs, int *i)
{
	t_list	*head;
	t_redir_data	*redir_content;
	(void)data;
	head = redir;
	while (head)
	{
		redir_content = head->content;
		if (redir_content->type == REDIR_HERE_DOC)
		{
			eofs[*i] = ft_strdup(redir_content->f_name);
			if (!eofs[*i])
				return (error("eofs", NULL, errno), 1);
			get_tmp_name(redir_content, -1, *i); // LEAKS???
			(*i)++;
		}
		head = head->next;
	}
	return (0);
}

static char	**store_eofs(t_node *tree, t_data *data, int n)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	char	**eofs;
	int		i;

	eofs = ft_calloc(n + 1, sizeof(char *));
	if (!eofs)
		return (error("eofs", NULL, errno), NULL);
	eofs[n] = NULL;
	i = 0;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (store_eofs_single_block(cmd->redir, data, eofs, &i))
			return (NULL);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (store_eofs_single_block(cmd->redir, data, eofs, &i))
		return (NULL);
	return (eofs);
}

static int	count_all_here_doc(t_list *redir, t_data *data)
{
	t_redir_data	*redir_content;
	int				n;
	(void)data;
	n = 0;
	if (!redir)
		return (0);
	while (redir)
	{
		redir_content = redir->content;
		if (redir_content->type == REDIR_HERE_DOC)
			n++;
		redir = redir->next;
	}
	return (n);
}

static int	get_n_eofs(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		n;

	n = 0;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		n += count_all_here_doc(cmd->redir, data);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	n += count_all_here_doc(cmd->redir, data);
	return (n);
}

char **collect_eofs(t_node *tree, t_data *data)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		n;
	char	**eofs;
	(void)pipe;
	(void)cmd;
	n = 0;
	n = get_n_eofs(tree, data);
	if (n == 0)
		return (NULL);
	eofs = store_eofs(tree, data, n);
	if (!eofs)
		data->e_code = 1;
	return (eofs);
}
