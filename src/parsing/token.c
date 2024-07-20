/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:01:39 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/13 12:02:15 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "../../include/lexer.h"
#include	"../../include/parser.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)ft_calloc1(1, sizeof(t_token));
	token->e_type = type;
	token->value = value;
	return (token);
}
