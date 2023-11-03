/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 14:56:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_cmd_tab_args(t_cmd *cmd, t_tkn_data *tkn_curr)
{
	ft_printf("   • Added [%s] to args\n", tkn_curr->str);
}
