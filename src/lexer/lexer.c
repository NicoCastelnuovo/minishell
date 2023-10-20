/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/20 07:54:37 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_token_data(t_list *token_node, char *token_content, t_list **token_head)
{
	t_token_data	*token_data;
	t_token_data	*token_head_data;

	token_data = malloc(sizeof(t_token_data));
	token_node->content = token_data;
	token_head_data = ((t_token_data *)(*token_head)->content);
	token_data->string = token_content;
	if (token_node == *token_head)
		token_data->length = token_head_data->length = 1;
	else
		token_head_data->length++;
	token_data->length = token_head_data->length;
	printf("token_head_data->length = %d\n", token_data->length);
	printf("token_head_data->content = %s\n", token_data->string);
}

char	*store_special_char_as_token(char *c, int special_char_counter, t_list **token_head)
{
	char	*special_char_string;
	t_list	*special_char_node;
	
	special_char_string = malloc((special_char_counter + 1) * sizeof(char));
	special_char_string[special_char_counter] = '\0';
	special_char_node = malloc(sizeof(t_list));
	ft_memset(special_char_string, *c, special_char_counter);
	printf("***special_character:%s\n", special_char_string);
	ft_lstadd_back(token_head, special_char_node);
	initialize_token_data(special_char_node, special_char_string, token_head);
	return (special_char_string);
}

char	*store_previous_chars_as_token(char *reference, int token_counter, t_list **token_head)
{
	char	*last_token_string;
	t_list	*last_token_node;

	if (token_counter < 2)
		return (NULL);
	last_token_string = malloc((token_counter) * sizeof(char));
	last_token_string[token_counter] = '\0';
	last_token_node = malloc(sizeof(t_list));
	ft_strlcpy(last_token_string, reference, token_counter);
	printf("last_token:%s\n", last_token_string);
	ft_lstadd_back(token_head, last_token_node);
	initialize_token_data(last_token_node, last_token_string, token_head);
	return (last_token_string);
}

char	*check_is_special_char(char c)
{
	char	*result;

	char	*special_characters = ">< \t\n\'\"\\|$";
	result = ft_strchr(special_characters, c);
	return (result);
}

int	check_for_second_special_char(char *input, char c, int *input_counter, int *token_counter, int *special_char_counter, t_list **token_head)
{
	if (c == '>' || c == '<')
	{
		if (input[*(input_counter) + 1] == c)
		{
			(*input_counter)++;
			(*token_counter)++;
			(*special_char_counter)++;
			store_special_char_as_token(&c, *special_char_counter, token_head);
			// return (1);
		}
		else
			store_special_char_as_token((char *)&(input[*input_counter]), *special_char_counter, token_head);
	}
	else
		store_special_char_as_token((char *)&(input[*input_counter]), *special_char_counter, token_head);
	*special_char_counter = 0;
	return (0);
}

void	read_input_char_by_char(char *input, char **reference, int *input_counter, int *token_counter, int *special_char_counter, t_list **token_head)
{
		if (check_is_special_char(input[*input_counter]))
	{
		(*special_char_counter)++;
		if (*token_counter > 1)
		{
			store_previous_chars_as_token(*reference, *token_counter, token_head);
		}
		check_for_second_special_char(input, input[*input_counter], input_counter, token_counter, special_char_counter, token_head);		
		*reference += *token_counter;
		*token_counter = 0;
	}
	(*input_counter)++;
	(*token_counter)++;
}

void	tokenize_input(const char *input, t_list **token_head)
{
	int		input_counter;
	int		token_counter;
	int		special_char_counter;
	char	*reference;

	reference = (char *)input;
	input_counter = 0;
	token_counter = 1;
	special_char_counter = 0;
	while (input[input_counter])
	{
		read_input_char_by_char((char *)input, &reference, &input_counter, &token_counter, &special_char_counter, token_head);
	}
	store_previous_chars_as_token(reference, token_counter, token_head);
	reference += token_counter;
	token_counter = 0;
}

char	*get_input(void)
{
	char	*input;

	input = readline("minishell:");
	return (input);
}

int	main(void)
{
	char	*input;
	t_list	*token_head;
	
	// input = get_input();
	input = "$USER$USER\"test\"";
	token_head = NULL;
	tokenize_input(input, &token_head);
	// free(input);
	return (0);
}