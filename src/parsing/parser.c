/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:08:23 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/21 14:00:48 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include    "../../include/lexer.h"
#include "../../include/builtin.h"
#include "../../libft/libft.h"

void	create_token_list(t_listtoken *head)
{
	t_list	*lst;

	lst = NULL;
	while (head)
	{
		ft_lstadd_back(&lst, ft_lstnew(fill_token(head->check_token)));
		head = head->next;
	}
	g_bin->token = lst;
}

void	create_stack(t_token *token, t_lexer *lexer)
{
	int			i;
	t_listtoken	*tmp;
	t_listtoken	*before;
	t_listtoken	*head;

	before = 0;
	i = 1;
	g_bin->exp_herdoc = 0;
	token = lexer_get_next_token(lexer);
	while ((token) != ((void *)0))
	{
		tmp = ft_leaks(sizeof(t_listtoken));
		tmp->check_token = ft_leaks(sizeof(t_token));
		tmp->next = NULL;
		tmp->check_token->value = token->value;
		tmp->check_token->e_type = token->e_type;
		if (i == 1)
			head = tmp;
		if (before != 0)
			before->next = tmp;
		before = tmp;
		i++;
		token = lexer_get_next_token(lexer);
	}
	create_token_list(head);
}

int	check_syntax_utils(t_list *token)
{
	t_list	*cmd;

	cmd = token;
	if (((t_token *)cmd->content)->e_type > 0 && !cmd->next)
		return (1);
	if (((((t_token *)cmd->content)->e_type == 1
				&& (((t_token *)cmd->next->content)->e_type) == 1)
			|| ((((t_token *)cmd->content)->e_type == 3
					&& ((t_token *)cmd->next->content)->e_type == 3))
			|| ((((t_token *)cmd->content)->e_type == 5
					&& ((t_token *)cmd->next->content)->e_type == 5))
			|| ((((t_token *)cmd->content)->e_type == 4
					&& ((t_token *)cmd->next->content)->e_type == 4))
			|| ((((t_token *)cmd->content)->e_type == 5
					&& ((t_token *)cmd->next->content)->e_type == 2))
			|| ((((t_token *)cmd->content)->e_type == 5
					&& ((t_token *)cmd->next->content)->e_type == 3))
			|| ((((t_token *)cmd->content)->e_type == 4
					&& ((t_token *)cmd->next->content)->e_type == 3))
			|| ((((t_token *)cmd->content)->e_type == 4
					&& ((t_token *)cmd->next->content)->e_type) == 1)
			|| ((((t_token *)cmd->content)->e_type == 5
					&& ((t_token *)cmd->next->content)->e_type) == 1)))
		return (1);
	return (0);
}

int	check_ambiguous_redirect(t_list *token)
{
	t_list	*cmd;

	cmd = token;
	if ((((t_token *)cmd->content)->e_type == 2
			|| ((t_token *)cmd->content)->e_type == 3
			|| ((t_token *)cmd->content)->e_type == 5)
		&& (((t_token *)cmd->next->content)->e_type == 0)
		&& (((t_token *)cmd->next->content)->value[0] == '\0'))
		return (1);
	return (0);
}

int	check_syntax(t_list *token)
{
	t_list	*cmd;

	cmd = token;
	while (cmd)
	{
		if (check_syntax_utils(token) == 1)
			return (set_exit(258));
		if (check_ambiguous_redirect(token) == 1)
			return (erreur(1, NULL, NULL, "ambiguous redirect"));
		cmd = cmd->next;
	}
	return (0);
}
