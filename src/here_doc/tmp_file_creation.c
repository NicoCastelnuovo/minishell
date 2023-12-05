/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:39:13 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/05 16:28:16 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_tmp_name(int n)
{
	char	*tmp_name; // remember to throw an error in case of >".tmp_" something
	char	*digits;

	digits = ft_itoa(n);
	if (!digits && n != 0)
		return (NULL);
	tmp_name = ft_strjoin(".tmp_", digits);
	free(digits);
	return(tmp_name);
}

/*
	The open() function set errno to EEXIST in case it tries to create a new
	file with the same name of an already existing file. In that case,
	get_fd_tmp() try to create a new file incrementing by 1 the value n, until
	it finds a unique .tmp_n file name.
	The while loop ends only in 3 conditions: a tmp file name is found, an
	error from build_tmp_name() occured, or INT_MAX is reached.
*/
int	get_fd_tmp(t_redir_data *redir_cont, int fd_tmp, int n)
{
	char	*tmp_name;

	tmp_name = NULL;
	while (fd_tmp == -1)
	{
		if (n == INT_MAX)
			return (error("here_doc", "INT_MAX", CE_HERE_DOC), -1);
		tmp_name = build_tmp_name(n);
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
	free(redir_cont->file_name);
	redir_cont->file_name = tmp_name;
	return (fd_tmp);
}
