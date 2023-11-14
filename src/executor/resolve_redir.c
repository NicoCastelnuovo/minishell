/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:43:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 17:30:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_outfile(t_list *redir)
{
	t_list			*head;
	t_redir_data	*content;
	char			*last;
	int				fd;

	fd = -1;
	last = NULL;
	head = redir;
	while (head)
	{
		content = (t_redir_data *)head->content;
		head = head->next;
	}
	return (fd);
}

int	get_last_infile(t_list *redir)
{
	t_list			*head;
	t_redir_data	*content;
	char			*last;
	int				fd;

	fd = -1;
	last = NULL;
	head = redir;
	while (head)
	{
		content = (t_redir_data *)head->content;
		if (content->type == REDIR_IN || content->type == REDIR_HERE_DOC)
		{
			last = content->file_name;
			if (access(last, F_OK | R_OK) != 0)
				return (error(last, errno), -1);
		}
		head = head->next;
	}
	fd = open(last, O_RDONLY);
	if (fd == -1)
		return (error(last, errno), -1);
	return (fd);
}

int	resolve_redir(t_cmd *cmd)
{
	if (cmd->redir)
	{

	}
	return (0);
}
