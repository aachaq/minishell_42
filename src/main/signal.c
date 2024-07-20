/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:48 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:48 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/builtin.h"
#include "../../include/lexer.h"

void	unlink_tmp(int sig)
{
	t_list	*list;

	list = g_bin->token;
	while (list)
	{
		if (((t_token *)list->content)->e_type == 4)
		{
			list = list->next;
			unlink(((t_token *)list->content)->value);
		}
		list = list->next;
	}
	(void) sig;
	exit(1);
}

void	signal_heredoc(int pid)
{
	if (pid == 0)
		signal(SIGINT, unlink_tmp);
	else
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// Regenerate the prompt on a newline
// Clear the previous text
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_bin->exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int	init_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	reset_signal(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (1);
}
