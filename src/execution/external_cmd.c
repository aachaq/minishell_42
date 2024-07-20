/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:34 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:34 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	p_free(char **path)
{
	char	**tmp;

	if (path == NULL)
		return (1);
	tmp = path;
	while (*tmp)
		free(*tmp++);
	free(path);
	return (1);
}

char	*find_cmd_path(char *extern_cmd)
{
	char	*r;
	char	**path;
	t_list	*tmp;
	size_t	i;

	if (extern_cmd == '\0')
		return (NULL);
	tmp = g_bin->env;
	while (tmp && !ft_strnstr(tmp->content, "PATH=", 5))
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	path = ft_split(tmp->content + 5, ':');
	i = 0;
	while (path[i])
	{
		r = ft_strjoin(path[i], "/");
		ft_strcat(&r, extern_cmd);
		if (!access(r, F_OK) && p_free(path))
			return (r);
		free(r);
		i++;
	}
	p_free(path);
	return (NULL);
}

char	**ft_ltoa(t_list *token)
{
	size_t	s;
	char	**r;
	size_t	i;

	i = 0;
	s = ft_lstsize(token);
	r = ft_calloc3(sizeof(char *), s + 1, "");
	while (i < s)
	{
		r[i] = ft_strdup(((t_token *) token->content)->value);
		token = token->next;
		i++;
	}
	return (r);
}

int	get_cmd_path(char **extern_cmd)
{
	size_t	z;

	if (!ft_strcmp(*extern_cmd, "~") || !ft_strncmp(*extern_cmd, "~/", 2) || \
		!ft_strcmp(*extern_cmd, ".") || !ft_strcmp(*extern_cmd, "..") || \
		!ft_strncmp(*extern_cmd, "./", 2) || !ft_strncmp(*extern_cmd, "../", 3))
		if (!get_path(&extern_cmd[0]))
			return (0);
	z = 0;
	while (extern_cmd[++z])
	{
		if (extern_cmd[z][0] != '~')
			continue ;
		if (!get_path(&extern_cmd[z]))
			return (0);
	}
	return (1);
}

int	external(t_list *token)
{
	char	**extern_cmd;
	char	*path;
	DIR		*directory;

	extern_cmd = ft_ltoa(token);
	if (get_cmd_path(extern_cmd) == 0)
		exit(erreur(1, extern_cmd[0], NULL, strerror(2)));
	if (*extern_cmd[0] == '/')
		path = ft_strdup(extern_cmd[0]);
	else
		path = find_cmd_path(extern_cmd[0]);
	if (path == NULL)
		exit (erreur(127, extern_cmd[0], NULL, "Command not found"));
	if (access(path, F_OK) != 0)
		exit (erreur(127, extern_cmd[0], NULL, "No such file or directory"));
	directory = opendir(path);
	if (directory != NULL && closedir(directory) == 0)
		exit (erreur(126, path, NULL, "is a directory"));
	if (access(path, X_OK) != 0)
		exit (erreur(126, extern_cmd[0], NULL, "permission denied"));
	set_exit(0);
	if (execve(path, extern_cmd, ft_get_env()) == -1)
		exit (erreur(errno, extern_cmd[0], NULL, strerror(errno)));
	return (1);
}
