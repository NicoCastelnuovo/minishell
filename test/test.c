#include "minishell.h"

// static char	*get_input(void)
// {
// 	char	*input;

// 	input = readline("minishell:");
// 	return (input);
// }

static void	lexer(char *input, t_list **tkns_head)
{
	tokenize_input(input, tkns_head);
	// free(input);
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
	char	*input;
	t_list	*tkns_head;
	t_list	*temp;

	input = "<'<	' \"<<<\"'>>>$USER123?_ads$test'  <\" cat | <infile1 ls '$PATH$new -l < infile2 >' \"outfile | 'grep test | cat \"$my var\"\" -e >outfile2 '\" | wc -l\" >>outfile2 '|' grep -e >> '\"$var\"'$last_var123_!-'	 '	 ";
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
	// input = "\"$USER21_'@#!'$USER123__)+(123dsa)\"";
	// input = "Hello '\"\"\" some tokens 	' continue after quotation is closed";
	// input = "\"'hello world some \"more\" 	text $data'\"";
	// input = "$USER";
	// input = " 	''";
	// input = "\"\"\"";
	// input = "\"'$\"\"";
	// input = "$12das___<";
	// input = "$_ads123!";
	// input = "$!a1_ads123!";
	// input = "\"$\"\"";
	// input = "$_";
	// input = "$ USER";
	// input = "\"HELLO	\"	'WORLD  '	";
	// input = "";
	// input = "$123>";
	// input = "$ USER";
	// input = "<<<>>>>>";
	// input = "''";
	// input = " ";
	// input = "anything ";
	// input = "'>> <<<' ";
	// input = get_input();
	if (!input)
		return (1);
	tkns_head = NULL;
	lexer(input, &tkns_head);
	temp = tkns_head;
	while (temp)
	{
		printf("string = %s\n", ((t_tkn_data *)temp->content)->str);
		printf("list_size = %d\n",((t_tkn_data *)temp->content)->list_size);
		printf("type = %d\n",((t_tkn_data *)temp->content)->type);
		printf("length = %u\n",((t_tkn_data *)temp->content)->str_len);
		printf("quote = %d\n", ((t_tkn_data *)temp->content)->quote);
		printf("quote_status = %d\n", ((t_tkn_data *)temp->content)->quote_status);
		printf("white_space_status = %d\n", ((t_tkn_data *)temp->content)->white_space);
		printf("------------------------------\n");
		temp = temp->next;
	}
	if (tkns_head)
		ft_lstclear(&tkns_head, free_token_data);
	return (0);
}