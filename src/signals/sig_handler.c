/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 18:05:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrl_c_pressed = 0;

/*
	SIGINT prints a new line.
	@line	rl_on_new_line() - tell the program to move to a new line
	@line	rl_redisplay() - update what is displayed, to reflect the buffer
*/
static void	handle_sa_newline(int sig_n)
{
	(void) sig_n;
	g_ctrl_c_pressed = 1;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_sig_handling(void)
{
	struct sigaction	sa_newline;
	struct sigaction	sa_ignore;
	sigset_t			set;

	ft_bzero(&sa_newline, sizeof(sa_newline));
	ft_bzero(&sa_ignore, sizeof(sa_ignore));

	sigemptyset(&set);
	sigaddset(&set, SIGINT);	// C
	sigaddset(&set, SIGQUIT);	// <backsl>

	// ctrl C
	sa_newline.sa_handler = &handle_sa_newline;
	sa_newline.sa_flags = 0;
	sa_newline.sa_mask = set;
	sigaction(SIGINT, &sa_newline, NULL);

	// ctrl <backsl> --- nothing
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	// sa_ignore.sa_mask = set;
	sigaction(SIGQUIT, &sa_ignore, NULL);
}
