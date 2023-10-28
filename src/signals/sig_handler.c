/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/28 11:03:14 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	kill -9 $(jobs -ps) - kill all the suspended job, done with ctrl-Z
*/

/*
	SIGINT prints a new line.
	@line	rl_on_new_line() - tell the program to move to a new line
	@line	rl_redisplay() - update what is displayed, to reflect the buffer
*/
static void	handle_sa_newline(int sig_n)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sa_exit(int sig_n)
{
	sig_global = 1;
	ft_putstr_fd("exit\n", 1);
	if (sig_global)
		exit(0);
}

void	init_sig_handling(void)
{
	struct sigaction	sa_newline;
	struct sigaction	sa_ignore;
	struct sigaction	sa_exit;
	int					i;
	sigset_t			set;

	// init zero
	ft_bzero(&sa_newline, sizeof(sa_newline));
	ft_bzero(&sa_ignore, sizeof(sa_ignore));
	ft_bzero(&sa_exit, sizeof(sa_exit));

	// init set
	sigemptyset(&set);
	sigaddset(&set, SIGINT);	// C
	sigaddset(&set, SIGQUIT);	// <backsl>
	sigaddset(&set, SIGABRT);	// D

	// ctrl C
	sa_newline.sa_handler = &handle_sa_newline;
	sa_newline.sa_flags = 0;
	sa_newline.sa_mask = set;
	sigaction(SIGINT, &sa_newline, NULL);

	// ctrl <backsl> --- nothing
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sa_ignore.sa_mask = set;
	sigaction(SIGQUIT, &sa_ignore, NULL);

	// ctrl D
	sa_exit.sa_handler = &handle_sa_exit;
	sa_exit.sa_flags = 0;
	sa_exit.sa_mask = set;
	sigaction(SIGABRT, &sa_exit, NULL);
}
