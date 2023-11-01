/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/01 12:50:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_env	*env_cpy;

	init_sig_handling();
	env_cpy = init_env(env);
	while (1)
	{
		line = readline("minishell $ ");
		if (ft_strncmp(line, "clear", ft_strlen("clear")) == 0)
			rl_clear_history();
		if (line && !is_empty_line(line))
			add_history(line);
		if (line)
			free(line);
	}
	return (0);
}
