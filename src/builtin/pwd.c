/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:14 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/20 10:40:58 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../libft/libft.h"

int	pwd(t_list *token, int fd)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd == NULL)
		return (erreur(errno, "pwd", NULL, "PWD not set"));
	if (token->next != NULL)
		return (erreur(1, "exit", NULL, "too many arguments"));
	ft_putendl_fd(pwd, fd);
	free(pwd);
	(void) token;
	return (g_bin->exit_status);
}
