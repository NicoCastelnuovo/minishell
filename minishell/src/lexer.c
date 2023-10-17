/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/17 09:31:19 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_current_token(char *c, int j)
{
	char	*special_character;

	special_character = malloc((j + 1) * sizeof(char));
	special_character[j] = '\0';
	ft_memset(special_character, *c, j);
	printf("***special_character:%s\n", special_character);
	return (special_character);
}

char	*store_ptrvioud_chars_as_token(char *reference, int j)
{
	char	*last_token;

	if (j < 2)
		return (NULL);
	last_token = malloc((j) * sizeof(char));
	last_token[j] = '\0';
	ft_strlcpy(last_token, reference, j);
	printf("last_token:%s\n", last_token);
	return (last_token);
}

char	*check_is_special_char(char c)
{
	char	*result;

	char	*special_characters = ">< \n\'\"\\|$";
	result = ft_strchr(special_characters, c);
	return (result);
}

int	store_special_char_as_token(char *input, char c, int *i, int *j)
{
	if (c == '>' || c == '<')
	{
		if (input[*(i) + 1] == c)
		{
			(*i)++;
			(*j)++;
			store_current_token(&c, *j);
			return (1);
		}
		else
			store_current_token((char *)&(input[*i]), *j);
	}
	else
		store_current_token((char *)&(input[*i]), *j);
	return (0);
}

void	read_input_char_by_char(char *input, char **reference, int *i, int *j)
{
	if (check_is_special_char(input[*i]))
	{
		if (*j > 1)
		{
			store_ptrvioud_chars_as_token(*reference, *j);
		}
		store_special_char_as_token(input, input[*i], i, j);		
		*reference += *j;
		*j = 0;
	}
	(*i)++;
	(*j)++;
}

void	read_input(const char *input)
{
	int		i;
	int		j;
	char	*reference;

	reference = (char *)input;
	i = 0;
	j = 1;
	while (input[i])
	{
		read_input_char_by_char((char *)input, &reference, &i, &j);
	}
	store_ptrvioud_chars_as_token(reference, j);
	reference += j;
	j = 0;
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
	input = "<< < cat | <infile1 ls -l < infile2 > outfile | grep test | cat -e >outfile2 | wc -l >>outfile2 | grep -e >>f";

	read_input(input);
	// free(input);
	return (0);
}