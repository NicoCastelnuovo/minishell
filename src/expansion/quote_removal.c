/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:34:59 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/22 08:46:32 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// "ls" | echo $"Hello $USER!" | echo $"USER" | echo "$USER" | echo '$USER' | echo $USER

/*
	ls - executed
	Hello ncasteln!
	USER
	-------
	ncasteln
	$USER
	ncasteln
*/

int	quote_removal(t_data *data)
{

}
