/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/30 15:32:09 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_input(void)
{
	char	*input;

	input = readline("minishell:");
	return (input);
}

static void	lexer(char *input, t_list **tkns_head)
{
	tokenize_input(input, tkns_head);
	free(input);
	assign_type_to_tkn(*tkns_head);
	assign_quote_status_to_tkn(*tkns_head);
	merge_consecutive_less_or_greater_than(*tkns_head);
	merge_dollar_char_with_next_token(*tkns_head);
	merge_quoted_tokens(*tkns_head);
	assign_following_space_status(*tkns_head);
	delete_not_quoted_spaces(tkns_head);
}

int	main(void)
{
	char		*input;
	t_list		*tkns_head;
	t_list		*temp;
	t_tkn_data	*tkn_data;

	input = get_input();
	if (!input)
		return (1);
	tkns_head = NULL;
	lexer(input, &tkns_head);
	temp = tkns_head;
	while (temp)
	{
		tkn_data = (t_tkn_data *)temp->content;
		printf("string = %s\n", tkn_data->str);
		printf("list_size = %d\n", tkn_data->list_size);
		printf("type = %d\n", tkn_data->type);
		printf("length = %u\n", tkn_data->str_len);
		printf("quote = %d\n", tkn_data->quote);
		printf("quote_status = %d\n", tkn_data->quote_status);
		printf("white_space_status = %d\n", tkn_data->white_space);
		printf("------------------------------\n");
		temp = temp->next;
	}
	if (tkns_head)
		ft_lstclear(&tkns_head, free_token_data);
	return (0);
}
