/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:01:02 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 13:01:02 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../include/lexer.h"
#include "../../libft/libft.h"

t_token	*fill_token(t_token *token)
{
	t_token	*r;

	r = ft_calloc(sizeof(t_token), 1);
	r->e_type = token->e_type;
	r->value = ft_strdup(token->value);
	return (r);
}

void	create_cmd(void)
{
	t_list	*list;
	t_list	*command;

	list = g_bin->token;
	command = NULL;
	while (list)
	{
		if (((t_token *)list->content)->e_type == token_pipe)
		{
			ft_lstadd_back(&g_bin->cmd, ft_lstnew(command));
			command = NULL;
		}
		else
			ft_lstadd_back(&command, ft_lstnew(fill_token(list->content)));
		list = list->next;
	}
	if (command != NULL)
		ft_lstadd_back(&g_bin->cmd, ft_lstnew(command));
}

int	lexer(char *str)
{
	int		i;
	t_lexer	*lexer;
	t_token	*token;

	i = 1;
	token = (void *)0;
	g_bin->leaks = malloc(sizeof(t_list *));
	*(g_bin->leaks) = NULL;
	g_bin->lexer_erreur = 0;
	if (cmp(str) == 1)
	{
		lexer = init_lexer(str);
		create_stack(token, lexer);
		if (g_bin->lexer_erreur)
		{
			ft_lstclear1(g_bin->leaks);
			return (0);
		}
		ft_lstclear1(g_bin->leaks);
	}
	return (1);
}

int	syntax_error(void)
{
	t_list	*list;

	list = g_bin->token;
	if (((t_token *)list->content)->e_type == 1)
		return (set_exit(258));
	while (list)
	{
		if (check_syntax(list))
			return (1);
		if (((t_token *)list->content)->e_type == 4)
		{
			list = list->next;
			if (child_here_doc(list->content))
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	parsing(void)
{
	if (g_bin->token == NULL)
		return (0);
	if (syntax_error())
	{
		if (g_bin->exit_status == 258)
			return (erreur(258, NULL, NULL, \
			"Syntax error near unexpected token") == 0);
		if (g_bin->exit_status == 1)
			return (0);
		return (erreur(errno, NULL, NULL, strerror(errno)) == 0);
	}
	create_cmd();
	return (1);
}
