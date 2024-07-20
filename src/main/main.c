/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:45 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/21 13:58:20 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../include/main.h"
#include "../../include/parser.h"
#include <unistd.h>

int	start_minishell(char **line)
{
	int	a;

	a = 1;
	(void)line;
	if (lexer(*line) == 0 || g_bin->token == NULL)
		a = 0;
	if (a)
		a = parsing();
	if (a)
		execute();
	return (1);
}

void	delete_cmd(void *cmd)
{
	t_list	*acmd;

	acmd = (t_list *)cmd;
	ft_lstclear(&acmd, delete_token);
}

int	init_variables(void)
{
	ft_lstclear(&g_bin->token, delete_token);
	ft_lstclear(&g_bin->cmd, delete_cmd);
	init_signal();
	manage_termios(1);
	dup2(g_bin->o_fd[0], 0);
	dup2(g_bin->o_fd[1], 1);
	return (1);
}

int	minishell(int ac, char **av, char **env)
{
	g_bin = ft_calloc3(sizeof(t_bin), 1, "");
	if (ac > 1 && access(av[1], F_OK) == -1)
		return (0);
	init_termios();
	if (*env == NULL)
	{
		erreur(1, NULL, NULL, "The Environment is ignored");
		exit(1);
	}
	init_env(ac, av, env);
	g_bin->o_fd[0] = dup(0);
	g_bin->o_fd[1] = dup(1);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	if (!minishell(ac, av, env))
		return (erreur(2, av[1], NULL, strerror(2)));
	while (1)
	{
		init_variables();
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd(" exit\n", 1);
			exit(0);
			return (0);
		}
		add_history(line);
		start_minishell(&line);
		free(line);
		free(g_bin->leaks);
	}
	return (0);
}
