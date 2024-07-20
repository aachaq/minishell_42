/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:30 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:30 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../libft/libft.h"
#include "../../include/main.h"
#include "../../include/lexer.h"

int	fd_pipe(t_list *cmd, int *fd, int child)
{
	if (child)
	{
		close(fd[0]);
		if (cmd->next != NULL)
			dup2(fd[1], 1);
		else
			dup2(g_bin->o_fd[1], 1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (cmd->next != NULL)
			dup2(fd[0], 0);
		else
			dup2(g_bin->o_fd[0], 0);
		close(fd[0]);
	}
	return (1);
}

int	ft_builtin(t_list *token, int child)
{
	t_token	*arg;
	int		fd;

	arg = (t_token *) token->content;
	if (fd_redirection(&token) == 0)
		return (1);
	if (child == 1)
		fd = 1;
	if (!ft_strcmp(arg->value, "exit"))
		fd = 2;
	set_exit(0);
	set_underscore();
	return (execute_builtin(token, fd));
}

int	p_child(t_list *cmd)
{
	pid_t			pid;

	if (pipe(g_bin->fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	reset_subsystem(pid, 0);
	if (pid == 0)
	{
		fd_pipe(cmd, g_bin->fd, 1);
		if (!fd_redirection((t_list **) &cmd->content))
			exit(g_bin->exit_status);
		if (check_builtin(cmd->content) && ft_builtin(cmd->content, 1) >= 0)
			exit(g_bin->exit_status);
		else
			external(cmd->content);
	}
	fd_pipe(cmd, g_bin->fd, 0);
	if (cmd->next != NULL && p_child(cmd->next))
		waitpid(pid, NULL, 0);
	else
		waitpid(pid, &g_bin->result, 0);
	g_bin->exit_status = WEXITSTATUS(g_bin->result);
	return (1);
}

int	execute(void)
{
	if (g_bin->cmd == NULL)
		return (0);
	if (g_bin->cmd->next == NULL && check_builtin(g_bin->cmd->content))
		return (ft_builtin(g_bin->cmd->content, 0));
	p_child(g_bin->cmd);
	set_underscore();
	return (g_bin->exit_status);
}
