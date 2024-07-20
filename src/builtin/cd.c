/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:58:45 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/17 17:40:23 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	set_path_env(char *oldpwd, char *pwd)
{
	char	*opwd;
	char	*cpwd;

	cpwd = ft_strjoin("PWD=", pwd);
	opwd = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(opwd);
	ft_export(cpwd);
	free(opwd);
	free(cpwd);
	return (0);
}

static int	cd_path(t_list *token, char *cwd, int fd)
{
	int				r;
	t_token			*arg;
	int				old_pwd;

	arg = (t_token *) token->next->content;
	old_pwd = (!ft_strcmp(arg->value, "-"));
	r = 0;
	if (!get_path(&arg->value))
	{
		r = 3;
		if (old_pwd)
			erreur(1, "cd", NULL, "OLDPWD not set");
		else
			erreur(1, "cd", NULL, "No such file or directory");
	}
	else if (arg->value == NULL || chdir(arg->value))
		r = errno;
	else if (old_pwd)
		ft_putendl_fd(arg->value, fd);
	set_path_env(cwd, arg->value);
	return (r);
}

static int	cd_home(char *cwd)
{
	char *const	home = get_home();
	int			r;

	r = 0;
	if (home == NULL)
	{
		r = 3;
		erreur(1, "cd", NULL, "Home not set");
	}
	else if (chdir(home))
		r = errno;
	set_path_env(cwd, home);
	if (home != NULL)
		free(home);
	return (r);
}

int	cd(t_list *token, int fd)
{
	char	*pathname;
	int		exit_s;

	pathname = ft_getcwd();
	if (pathname == NULL)
		return (erreur(errno, "cd", NULL, "PWD not set"));
	if (ft_lstsize(token) == 1)
		exit_s = cd_home(pathname);
	else
		exit_s = cd_path(token, pathname, fd);
	free(pathname);
	if (exit_s == 3)
		exit_s = 1;
	else if (exit_s)
		erreur(errno, "cd", NULL, strerror(errno));
	return (set_exit(exit_s));
}
