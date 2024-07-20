/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachaq <aachaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:46:14 by aachaq            #+#    #+#             */
/*   Updated: 2023/02/10 12:52:39 by aachaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"lexer.h"
# include "../libft/libft.h"
# include "../libft/libft.h"

typedef struct s_exp
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*str5;
	char	*str6;
	char	*str7;
	char	*str8;
	char	*str3_1;
	int		end;
	int		start;
	char	c;
}	t_exp;

typedef struct s_leaks
{
	struct s_leaks	*next;
	void			*ptr;
}	t_leaks;

typedef struct s_listtoken
{
	struct s_listtoken	*next;
	t_token				*check_token;
}		t_listtoken;

// traiter_string.c
int			count_double_cout(char *str);
int			ft_cmp(char *s1, char *s2);
char		*expand_var_str(char *str);
int			is_alpha_number_indescor(char c);
// traiter_string1.c
char		*cut_var_string(char *str);
char		*rechercher_var(char *str);
int			find_close_double_cout(char *str, int i);
int			find_close_single_cout(char *str, int i);
char		*expand(char *str);
// traiter_string2.c
char		*expand_string(char *str, int s1_end, int s2_start);
char		*expand_str_cout(char *str);
char		*fonction_single_cout(char *str, int s1_end, int s2_start);
char		*fonction_double_cout(char *str, int s1_end, int s2_start);
char		*print_code_error(void);
// traiter_string3.c
char		*traiter_string(char *str);
char		*cut_var_string(char *str);
char		*ft_itoa1(int n);
//ft_malloc.c
void		ft_lstclear1(t_list **lst);
void		*ft_leaks(size_t size);
//cmd
int			lexer(char *str);
int			parsing(void);
int			check_syntax(t_list *token);
void		create_stack(t_token *token, t_lexer *lexer);
t_token		*fill_token(t_token *token);
//here_document.c
int			child_here_doc(t_token *token);

#endif