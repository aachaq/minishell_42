/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:24 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/21 13:59:04 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"

static int	d_last(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp->next == NULL)
	{
		free(tmp->content);
		free(tmp);
		*lst = NULL;
		return (1);
	}
	while (tmp->next->next)
		tmp = tmp->next;
	free(tmp->next->content);
	free(tmp->next);
	tmp->next = NULL;
	return (1);
}

static int	b_list(t_list **lst, char *path)
{
	char	*token;

	token = NULL;
	while (*path)
	{
		ft_strncat(&token, path, 1);
		if (*path == '/' || *(path + 1) == '\0')
		{
			if (ft_strcmp(token, ".") == 0 || ft_strcmp(token, "./") == 0)
				free(token);
			else if (!ft_strcmp(token, "..") || !ft_strcmp(token, "../"))
			{
				free(token);
				d_last(lst);
			}
			else
				ft_lstadd_back(lst, ft_lstnew(token));
			token = NULL;
		}
		path++;
	}
	return (1);
}

char	*absolute_path(char *path)
{
	char	*r;

	if (*path == '\0')
		r = ft_getcwd();
	else if (!ft_strcmp(path, "-"))
		r = get_oldpwd();
	else if (!ft_strcmp(path, "~") || !ft_strncmp(path, "~/", 2))
		r = get_home();
	else if (*path != '/')
		r = ft_getcwd();
	else
		r = ft_strdup(path);
	if (r == NULL)
		return (NULL);
	if (!ft_strcmp(path, "~") || !ft_strncmp(path, "~/", 2))
		ft_strcat(&r, path + 1);
	else if (*path != '\0' && *path != '-' && *path != '/')
	{
		ft_strcat(&r, "/");
		ft_strcat(&r, path);
	}
	return (r);
}

char	*relative_path(char *path)
{
	char	*r;
	t_list	*lst;
	t_list	*tmp;

	r = NULL;
	lst = NULL;
	b_list(&lst, path);
	tmp = lst;
	while (tmp->next)
	{
		ft_strcat(&r, tmp->content);
		tmp = tmp->next;
	}
	if (((char *) tmp->content)[ft_strlen(tmp->content) - 1] == '/')
		ft_strncat(&r, tmp->content, ft_strlen(tmp->content) - 1);
	else
		ft_strcat(&r, tmp->content);
	ft_lstclear(&lst, free);
	return (r);
}

int	get_path(char **path)
{
	char		*first;
	char		*second;

	first = absolute_path(*path);
	if (first == NULL)
		return (0);
	second = relative_path(first);
	if (second == NULL)
		return (0);
	free(*path);
	if (access(second, F_OK) == 0)
	{
		*path = second;
		free(first);
	}
	else
	{
		*path = first;
		free(second);
	}
	return (1);
}
