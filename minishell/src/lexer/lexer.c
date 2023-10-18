/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/17 15:40:52 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_special_char_as_token(char *c, int special_char_counter)
{
	char	*special_character;

	special_character = malloc((special_char_counter + 1) * sizeof(char));
	special_character[special_char_counter] = '\0';
	ft_memset(special_character, *c, special_char_counter);
	printf("***special_character:%s\n", special_character);
	return (special_character);
}

char	*store_previous_chars_as_token(char *reference, int token_counter)
{
	char	*last_token;

	if (token_counter < 2)
		return (NULL);
	last_token = malloc((token_counter) * sizeof(char));
	last_token[token_counter] = '\0';
	ft_strlcpy(last_token, reference, token_counter);
	printf("last_token:%s\n", last_token);
	return (last_token);
}

char	*check_is_special_char(char c)
{
	char	*result;

	char	*special_characters = ">< \t\n\'\"\\|$";
	result = ft_strchr(special_characters, c);
	return (result);
}

int	check_for_second_special_char(char *input, char c, int *input_counter, int *token_counter, int *special_char_counter)
{
	if (c == '>' || c == '<')
	{
		if (input[*(input_counter) + 1] == c)
		{
			(*input_counter)++;
			(*token_counter)++;
			(*special_char_counter)++;
			store_special_char_as_token(&c, *special_char_counter);
			// return (1);
		}
		else
			store_special_char_as_token((char *)&(input[*input_counter]), *special_char_counter);
	}
	else
		store_special_char_as_token((char *)&(input[*input_counter]), *special_char_counter);
	*special_char_counter = 0;
	return (0);
}

void	read_input_char_by_char(char *input, char **reference, int *input_counter, int *token_counter, int *special_char_counter)
{
		if (check_is_special_char(input[*input_counter]))
	{
		(*special_char_counter)++;
		if (*token_counter > 1)
		{
			store_previous_chars_as_token(*reference, *token_counter);
		}
		check_for_second_special_char(input, input[*input_counter], input_counter, token_counter, special_char_counter);		
		*reference += *token_counter;
		*token_counter = 0;
	}
	(*input_counter)++;
	(*token_counter)++;
}

void	tokenize_input(const char *input)
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
		read_input_char_by_char((char *)input, &reference, &input_counter, &token_counter, &special_char_counter);
	}
	store_previous_chars_as_token(reference, token_counter);
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
	
	// input = get_input();
	input = "$USER$USER";
	tokenize_input(input);
	// free(input);
	return (0);
}