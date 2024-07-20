/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:16:28 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/16 14:25:28 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stddef.h>

typedef struct s_lexerstruct
{
	char			c;
	unsigned int	i;
	char			*contents;
}	t_lexer;

typedef struct s_tokenstruct
{
	enum
	{
		token_string,
		token_pipe,
		token_red_input,
		token_red_output,
		token_herdoc,
		token_appand
	}	e_type;
	char	*value;
}	t_token;

t_token	*init_token(int type, char *value);

t_lexer	*init_lexer(char *contents);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
char	*traiter_string(char *str);
char	*traiter_string(char *str);
//lexer_utils.c
char	*ft_strjoin2(char const *s1, char const *s2);
void	*ft_calloc1(size_t count, size_t size);
char	*ft_substr1(char *s, int start, size_t len);
char	*ft_strdup1(char *s);
t_token	*get_string(t_lexer *lexer);
//traiter_string.c
int		cmp(char *s1);	

#endif
