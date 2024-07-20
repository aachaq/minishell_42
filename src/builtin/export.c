/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:10 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/20 16:23:43 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	check_var(const char *var)
{
	if (*var == 0)
		return (1);
	if (!ft_isalpha(*var) && *var != '_')
		return (1);
	while (*var)
	{
		if (*var == '=')
			break ;
		if (!ft_isalnum(*var) && *var != '_')
			return (1);
		var++;
	}
	return (0);
}

int	replace_env(t_list *env, const char *value)
{
	if (!ft_strchr(value, '='))
		return (1);
	if (env->content != NULL)
		free(env->content);
	env->content = ft_strdup(value);
	return (1);
}

int	print_e(int fd)
{
	t_list	*env;
	char	*c;

	env = g_bin->env;
	while (env->next)
	{
		ft_putstr_fd("declare -x", fd);
		c = env->content;
		while (*c && *c != '=')
			ft_putchar_fd(*c++, fd);
		if (*c == '=')
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(c + 1, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (g_bin->exit_status);
}

int	ft_export(char *var)
{
	t_list	*last;
	t_list	*env;

	last = ft_lstlast(g_bin->env);
	env = ft_env((const char *)var);
	if (env == NULL)
	{
		ft_lstadd_back(&g_bin->env, ft_lstnew(ft_strdup(var)));
		ft_swap(&last->content, &last->next->content);
	}
	else
		replace_env(env, var);
	return (1);
}

int	export(t_list *token, int fd)
{
	char	*var;

	if (ft_lstsize(token) == 1)
		return (print_e(fd));
	token = token->next;
	while (token)
	{
		var = ((t_token *) token->content)->value;
		if (check_var(var))
			erreur(1, "export", var, "not a valid identifier");
		else
			ft_export(var);
		token = token->next;
	}
	return (g_bin->exit_status);
}
