/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/20 16:00:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *input, t_list **tkns_head)
{
	tokenize_input(input, tkns_head);
	assign_type_to_tkn(*tkns_head);
	assign_quote_status_to_tkn(*tkns_head);
	merge_consecutive_less_or_greater_than(*tkns_head);
	merge_dollar_char_with_next_token(*tkns_head);
	merge_quoted_tokens(*tkns_head);
	assign_following_space_status(*tkns_head);
	delete_not_quoted_spaces(tkns_head);
}
