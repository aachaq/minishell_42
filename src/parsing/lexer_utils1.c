/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:17:39 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/20 22:12:29 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/parser.h"
#include    "../../include/lexer.h"
#include "../../include/builtin.h"
#include "../../libft/libft.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)ft_calloc1(1, sizeof(t_lexer));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

t_token	*get_str_utls(char *str, int start, int end)
{
	char	*str1;

	str1 = traiter_string(ft_substr1(str, start, end));
	return (init_token(token_string, str1));
}

t_token	*get_string(t_lexer *lexer)
{
	t_exp	exp;

	exp.end = 0;
	exp.start = lexer->i;
	while (lexer->c != ' ' && lexer->c != '\t'
		&& lexer->c != '\n' && lexer->c != '\0')
	{	
		if (lexer->c == '"' || lexer->c == '\'')
		{
			exp.c = lexer->c;
			lexer_advance(lexer);
			while (lexer->c != exp.c && lexer->c != '\0')
			{
				lexer_advance(lexer);
				exp.end++;
			}
			exp.end++;
		}
		if (lexer->c == '>' || lexer->c == '<'
			|| lexer->c == '|')
			break ;
		lexer_advance(lexer);
		exp.end++;
	}
	return (get_str_utls(lexer->contents, exp.start, exp.end));
}
