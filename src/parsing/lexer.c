/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:13:03 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/16 14:25:18 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include    "../../include/lexer.h"
#include "../../include/builtin.h"
#include "../../libft/libft.h"

t_token	*get_redirec_right(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '>')
	{
		lexer_advance(lexer);
		return (init_token(token_appand, ft_strdup1(">>")));
	}
	else
		return (init_token(token_red_output, ft_strdup1(">")));
}

t_token	*get_redirec_left(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '<')
	{
		lexer_advance(lexer);
		g_bin->exp_herdoc = 1;
		return (init_token(token_herdoc, ft_strdup1("<<")));
	}
	else
		return (init_token(token_red_input, ft_strdup1("<")));
}

t_token	*get_pipe(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (init_token(token_pipe, ft_strdup1("|")));
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
	{
		lexer_advance(lexer);
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->c != '\n')
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
		else if (lexer->c == '|')
			return (get_pipe(lexer));
		else if (lexer->c == '<')
			return (get_redirec_left(lexer));
		else if (lexer->c == '>')
			return (get_redirec_right(lexer));
		else
			return (get_string(lexer));
	}
	return ((void *)0);
}
