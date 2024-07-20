/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:18 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/17 16:42:00 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	check_env_var(t_list *env, char *var)
{
	size_t	var_env_len;
	size_t	var_len;

	var_env_len = ft_strlen(env->content);
	if (ft_strchr(env->content, '='))
		var_env_len = ft_strchr(env->content, '=') - (char *) env->content;
	var_len = ft_strlen(var);
	if (var_env_len != var_len)
		return (0);
	return (ft_strncmp(env->content, var, var_env_len) == 0);
}

int	d_unset(char *var)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = g_bin->env;
	while (current)
	{
		if (check_env_var(current, var))
		{
			if (previous == NULL)
				g_bin->env = current->next;
			else
				previous->next = current->next;
			ft_lstdelone(current, free);
			if (previous == NULL)
				current = g_bin->env;
			else
				current = previous->next;
			continue ;
		}
		previous = current;
		current = current->next;
	}
	return (1);
}

int	unset(t_list *token, int fd)
{
	t_token	*arg;

	token = token->next;
	while (token)
	{
		arg = token->content;
		if (check_var(arg->value))
			erreur(1, "unset", arg->value, "not a valid identifier");
		else
			d_unset(arg->value);
		token = token->next;
	}
	(void) fd;
	return (g_bin->exit_status);
}
