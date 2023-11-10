/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:06:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/10 07:20:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_custom(t_data *data)
{
	free_data(data);
	// free env !!!!!
	ft_putstr_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
