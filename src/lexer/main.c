/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 15:34:17 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*input;

	input = readline("minishell:");
	return (input);
}

void	tokenize_input(char *input, t_list **tkn_head)
{
	int		input_counter;
	int		tkn_counter;
	char	*ref;

	ref = input;
	input_counter = 0;
	tkn_counter = 1;
	while (input[input_counter])
	{
		read_char(input[input_counter], &ref, &tkn_counter, tkn_head);
		input_counter++;
		tkn_counter++;
	}
	store_prev_chars_as_tkn(ref, tkn_counter, tkn_head);
	ref += tkn_counter;
	tkn_counter = 0;
}

int	main(void)
{
	char	*input;
	t_list	*tokens_head;
	t_list	*temp;

	// input = get_input();
	input = "<'<'   <\" cat | <infile1 ls ' -l < infile2 >' \"outfile | 'grep test | cat \"\"\" -e >outfile2 '\" | wc -l\" >>outfile2 '|' grep -e >> '\"$var\"''";
	// input = "\"'$USER\"\"''\"\"\"'\"'test\"'$\"\"";
	// input = "ls | cat > outfile";
	// input = "<f";
	if (!input)
		return (1);
	tokens_head = NULL;
	tokenize_input(input, &tokens_head);
	// free(input);
	assign_type_to_tkn(tokens_head);
	assign_position_to_tkn(tokens_head);
	temp = tokens_head;
	while (temp)
	{
		printf("string = %s\n", ((t_token_data *)temp->content)->str);
		// printf("list_size = %d\n",((t_token_data *)temp->content)->list_size);
		printf("type = %d\n",((t_token_data *)temp->content)->type);
		printf("string_length = %u\n",((t_token_data *)temp->content)->str_len);
		printf("%s => position = %d\n", ((t_token_data *)temp->content)->str, ((t_token_data *)temp->content)->position);
		temp = temp->next;
	}
	free_tokens(&tokens_head);
	return (0);
}
