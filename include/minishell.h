/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 12:27:15 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "typedef.h"
# include "stdbool.h"

// t_token_data	*create_node(void *content, int type);
// t_token_data	*add_node_to_linked_list(t_token_data *head, void *content, int type);
void			free_tokens(t_list **token_head);

#endif
