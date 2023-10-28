/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/28 09:30:16 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sa_int(int sig_n)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_sig_handling(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_abrt;
	int					i;
	sigset_t			set;

	// init set
	sigemptyset(&set);
	sigaddset(&set, SIGINT);	// C
	sigaddset(&set, SIGQUIT);	// <backsl>
	sigaddset(&set, SIGABRT);	// D

	// ctrl C
	sa_int.sa_handler = &handle_sa_int;
	sa_int.sa_flags = 0;
	sa_int.sa_mask = set;
	sigaction(SIGINT, &sa_int, NULL);

	// ctrl <backsl> --- nothing
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sa_quit.sa_mask = set;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
