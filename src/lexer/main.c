/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 11:29:50 by fahmadia         ###   ########.fr       */
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
	if (*ref != '\0')
		ref += tkn_counter;
	tkn_counter = 0;
}

int	main(void)
{
	char	*input;
	t_list	*tkns_head;
	t_list	*temp;

	// input = get_input();
	// input = "<'<	' \"<<<\"'>>>'  <\" cat | <infile1 ls ' -l < infile2 >' \"outfile | 'grep test | cat \"\"\" -e >outfile2 '\" | wc -l\" >>outfile2 '|' grep -e >> '\"$var\"''	 '	 ";
	// input = "\"'$USER\"\"''\"\"\"'\"'test\"'$\"\"";
	// input = "ls | cat > outfile";
	// input = "<f";
	// input = "ls		'\"'\"	'\"''''\"		<< $var	-la | \\ --version \n";
	// input = ">'><<<";
	// input = ">>< > < ASD asd ' \" > < <<< >>><>>< >";
	// input = "  '\"a\"'";
	// input = "  		 	 f  	 	'	\"	 '	 	 	 ";
	// input = "f>";
	// input = " 	$USER123_!@#123123'< $PATH_123?\\	'	";
	input = "\"$USER21_@#!$USER123__)+(123dsa)\"";
	if (!input)
		return (1);
	tkns_head = NULL;
	tokenize_input(input, &tkns_head);
	// free(input);
	assign_type_to_tkn(tkns_head);
	assign_quotation_to_tkn(tkns_head);
	find_consecutive_less_or_greater_than(tkns_head);
	delete_spaces(&tkns_head);
	merge_dollar_char_with_next_token(tkns_head);
	temp = tkns_head;
	while (temp)
	{
		printf("string = %s\n", ((t_token_data *)temp->content)->str);
		printf("list_size = %d\n",((t_token_data *)temp->content)->list_size);
		printf("type = %d\n",((t_token_data *)temp->content)->type);
		printf("length = %u\n",((t_token_data *)temp->content)->str_len);
		printf("position = %d\n", ((t_token_data *)temp->content)->quotation);
		printf("------------------------------\n");
		temp = temp->next;
	}
	if (tkns_head)
		free_tokens(&tkns_head);
	return (0);
}


