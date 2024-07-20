/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:58:56 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:58:56 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"

int	init_env(int ac, char **av, char **env)
{
	char *const	last = ft_strjoin("_=", av[ac - 1]);
	char *const	shlvl = ft_strdup("SHLVL=");
	char		*lvl;

	lvl = NULL;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "SHLVL", 5) == 0)
			lvl = ft_itoa(ft_atoi(*env + 6) + 1);
		if (ft_strncmp(*env, "OLDPWD", 6) == 0)
			env++;
		else
			ft_lstadd_back(&g_bin->env, ft_lstnew(ft_strdup(*env++)));
	}
	if (lvl == NULL || ft_atoi(lvl) <= 0)
		ft_strcat((char **) &shlvl, "1");
	else
		ft_strcat((char **) &shlvl, lvl);
	free(lvl);
	ft_export(shlvl);
	ft_export(last);
	free(shlvl);
	free(last);
	return (1);
}

t_list	*ft_env(const char *value)
{
	t_list	*r;
	size_t	len_value;
	size_t	len_key;

	r = g_bin->env;
	len_value = ft_strlen(value);
	if (ft_strchr(value, '='))
		len_value = ft_strchr(value, '=') - value;
	while (r)
	{
		len_key = ft_strlen(r->content);
		if (ft_strchr(r->content, '='))
			len_key = ft_strchr(r->content, '=') - (char *) r->content;
		if (len_value == len_key && \
			ft_strncmp(r->content, value, len_key) == 0)
			return (r);
		r = r->next;
	}
	return (NULL);
}

int	env(t_list *token, int fd)
{
	t_list	*list;
	char	*env;

	list = g_bin->env;
	while (list != NULL)
	{
		env = (char *) list->content;
		if (ft_strchr(env, '='))
			ft_putendl_fd(env, fd);
		list = list->next;
	}
	(void) token;
	return (g_bin->exit_status);
}
