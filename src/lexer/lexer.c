/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 11:33:01 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_token_data(t_list *token_node, char *token_string, t_list **token_head)
{
	t_token_data	*token_data;
	t_token_data	*token_head_data;
	size_t			string_length;

	string_length = ft_strlen(token_string);
	token_data = malloc(1 * sizeof(t_token_data));
	token_node->content = token_data;
	token_head_data = ((t_token_data *)(*token_head)->content);
	token_data->string = token_string;
	if (token_node == *token_head)
		token_data->list_size = token_head_data->list_size = 1;
	else
		token_head_data->list_size++;
	token_data->list_size = token_head_data->list_size;
	token_data->type = 0;
	token_data->position = 0;
	token_data->string_length = string_length;
}

char	*store_special_char_as_token(char *c, t_list **token_head)
{
	char	*special_char_string;
	t_list	*special_char_node;
	
	special_char_string = malloc((1 + 1) * sizeof(char));
	if (!special_char_string)
		return (NULL);
	special_char_string[1] = '\0';
	special_char_node = malloc(1 * sizeof(t_list));
	if (!special_char_node)
		return (NULL);
	special_char_node->content = NULL;
	special_char_node->next = NULL;
	ft_memset(special_char_string, *c, 1);
	// printf("***special_character:%s\n", special_char_string);
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
	if (!last_token_string)
		return (NULL);
	last_token_string[token_counter - 1] = '\0';
	last_token_node = malloc(1 * sizeof(t_list));
	if (!last_token_node)
		return (NULL);
	last_token_node->content = NULL;
	last_token_node->next = NULL;
	ft_strlcpy(last_token_string, reference, token_counter);
	// printf("last_token:%s\n", last_token_string);
	ft_lstadd_back(token_head, last_token_node);
	initialize_token_data(last_token_node, last_token_string, token_head);
	return (last_token_string);
}

char	*check_is_special_char(char c)
{
	char	*result;
	char	*special_characters;

	special_characters = ">< \t\n\'\"\\|$";
	result = ft_strchr(special_characters, c);
	return (result);
}

void	read_input_char_by_char(char current_input, char **reference, int *token_counter, t_list **token_head)
{
	if (check_is_special_char(current_input))
	{
		if (*token_counter > 1)
		{
			store_previous_chars_as_token(*reference, *token_counter, token_head);
			*reference += *token_counter - 1;
			store_special_char_as_token(*reference, token_head);	
			(*reference)++;
			*token_counter = 0;
		}
		else
		{
			store_special_char_as_token(*reference, token_head);	
			(*reference)++;
			*token_counter = 0;
		}
	}
}

void	tokenize_input(char *input, t_list **token_head)
{
	int		input_counter;
	int		token_counter;
	char	*reference;

	reference = input;
	input_counter = 0;
	token_counter = 1;
	while (input[input_counter])
	{
		read_input_char_by_char(input[input_counter], &reference, &token_counter, token_head);
		input_counter++;
		token_counter++;
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

void	check_each_token_string(t_token_data *token_data)
{
	char token_first_char = *(token_data->string);
	if (token_first_char == REDIRECT_IN)
		token_data->type = REDIRECT_IN;
	else if (token_first_char == REDIRECT_OUT)
		token_data->type = REDIRECT_OUT;
	else if (token_first_char == WHITESPACE)
		token_data->type = WHITESPACE;
	else if (token_first_char == NEW_LINE)
		token_data->type = NEW_LINE;
	else if (token_first_char == SINGLE_QUOTE)
		token_data->type = SINGLE_QUOTE;
	else if (token_first_char == DOUBLE_QUOTE)
		token_data->type = DOUBLE_QUOTE;
	else if (token_first_char == ESCAPE_CHAR)
		token_data->type = ESCAPE_CHAR;
	else if (token_first_char == PIPE)
		token_data->type = PIPE;
	else if (token_first_char == DOLLAR_CHAR)
		token_data->type = DOLLAR_CHAR;
	else
		token_data->type = WORD;
}

void	assign_type_to_token(t_list *tokens_head)
{
	t_list			*temp;
	t_token_data	*token_data;

	temp = tokens_head;
	while (temp)
	{
		token_data = (t_token_data *)(temp->content);
		check_each_token_string(token_data);
		temp = temp->next;
	}
}

void	detect_quote(char token_first_char, bool *is_double_quote_open, bool *is_single_quote_open, t_position *position)
{
	if (token_first_char == DOUBLE_QUOTE && !*is_double_quote_open && !*is_single_quote_open)
	{
		*is_double_quote_open = true;
		*position = IN_DOUBLE_QUOTE;
		printf("double quote is open\n");
	}
	else if (token_first_char == DOUBLE_QUOTE && *is_double_quote_open && *position == IN_DOUBLE_QUOTE)
	{
		*is_double_quote_open = false;
		*position = NOT_QUOTED;
		printf("double quote is closed\n");
	}
	else if (token_first_char == SINGLE_QUOTE && !*is_single_quote_open && !*is_double_quote_open)
	{
		*is_single_quote_open = true;
		*position = IN_SINGLE_QUOTE;
		printf("single quote is open\n");
	}
	else if (token_first_char == SINGLE_QUOTE && *is_single_quote_open && *position == IN_SINGLE_QUOTE)
	{
		*is_single_quote_open = false;
		*position = NOT_QUOTED;
		printf("single quote is closed\n");
	}
}

void	assign_position_to_token(t_list *tokens_head)
{
	bool		is_single_quote_open;
	bool		is_double_quote_open;
	t_list		*current_node;
	char		token_first_char;
	t_position	position;

	position = NOT_QUOTED;
	is_single_quote_open = false;
	is_double_quote_open = false;
	current_node = tokens_head;
	while (current_node)
	{
		token_first_char = *(((t_token_data *)(current_node->content))->string);
		detect_quote(token_first_char, &is_double_quote_open, &is_single_quote_open, &position);
		((t_token_data *)(current_node->content))->position = position;
		if (((t_token_data *)(current_node->content))->position == IN_SINGLE_QUOTE && token_first_char == SINGLE_QUOTE)
			((t_token_data *)(current_node->content))->position = NOT_QUOTED;
		if (((t_token_data *)(current_node->content))->position == IN_DOUBLE_QUOTE && token_first_char == DOUBLE_QUOTE)
			((t_token_data *)(current_node->content))->position = NOT_QUOTED;
		current_node = current_node->next;
	}
}


int	main(void)
{
	char	*input;
	t_list	*tokens_head;
	
	// input = get_input();
	// input = "<'<'   <\" cat | <infile1 ls ' -l < infile2 >' \"outfile | 'grep test | cat \"\"\" -e >outfile2 '\" | wc -l\" >>outfile2 '|' grep -e >> '\"$var\"'";
	// input = "\"'$USER\"\"''\"\"\"'\"'test\"'$\"";
	// input = "ls | cat > outfile";
	input = "<f";
	if (!input)
		return (1);
	tokens_head = NULL;
	tokenize_input(input, &tokens_head);
	// free(input);
	assign_type_to_token(tokens_head);
	assign_position_to_token(tokens_head);
	t_list *temp = tokens_head;
	while (temp)
	{
		printf("string = %s\n",((t_token_data *)temp->content)->string);
		// printf("list_size = %d\n",((t_token_data *)temp->content)->list_size);
		printf("type = %d\n",((t_token_data *)temp->content)->type);
		printf("string_length = %u\n",((t_token_data *)temp->content)->string_length);
		printf("%s => position = %d\n", ((t_token_data *)temp->content)->string, ((t_token_data *)temp->content)->position);
		temp = temp->next;
	}
	free_tokens(&tokens_head);
	return (0);
}
