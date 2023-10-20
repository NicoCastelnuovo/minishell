/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/20 15:41:35 by fahmadia         ###   ########.fr       */
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
	token_data->string_length = string_length;
	// printf("token_head_data->length = %d\n", token_data->list_size);
	// printf("token_head_data->content = %s\n", token_data->string);
}

char	*store_special_char_as_token(char *c, t_list **token_head)
{
	char	*special_char_string;
	t_list	*special_char_node;
	
	special_char_string = malloc((1 + 1) * sizeof(char));
	special_char_string[1] = '\0';
	special_char_node = malloc(1 * sizeof(t_list));
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
	last_token_string[token_counter - 1] = '\0';
	last_token_node = malloc(1 * sizeof(t_list));
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

void	read_input_char_by_char(char cuurent_input, char **reference, int *token_counter, t_list **token_head)
{
	if (check_is_special_char(cuurent_input))
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

	reference = (char *)input;
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

int	main(void)
{
	char	*input;
	t_list	*token_head;
	
	// input = get_input();
	input = "<<   < cat | <infile1 ls -l < infile2 > outfile | grep test | cat -e >outfile2 | wc -l >>outfile2 | grep -e >>";
	// input = "ls | cat > outfile";
	token_head = NULL;
	tokenize_input(input, &token_head);
	// free(input);
	t_list *temp = token_head;
	while (temp)
	{
		printf("string = %s\n",((t_token_data *)temp->content)->string);
		printf("list_size = %d\n",((t_token_data *)temp->content)->list_size);
		printf("type = %d\n",((t_token_data *)temp->content)->type);
		printf("string_length = %u\n",((t_token_data *)temp->content)->string_length);
		temp = temp->next;
	}
	
	free_tokens(&token_head);
	return (0);
}