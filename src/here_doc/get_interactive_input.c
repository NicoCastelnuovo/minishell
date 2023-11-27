/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_interactive_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:39:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/27 10:39:50 by ncasteln         ###   ########.fr       */
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
				line = expand(line, data);
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
	The here_doc behaves differently if EOF is enclosed or not in quotes. If
	it contains quotes, the environment var and $? are not expanded; if EOF
	has no quote, they are expanded.
*/
static int	get_interactive_input(int fd_tmp, char **eof, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(*eof, TKN_S_QUOTE) || ft_strchr(*eof, TKN_D_QUOTE))
	{
		tmp = *eof;
		*eof = remove_quote_pairs(*eof);
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

int	perform_here_doc(t_redir_data *redir_content, t_data *data)
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
