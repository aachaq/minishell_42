/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:27:46 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/14 09:27:46 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../include/main.h"

void	manage_termios(int a)
{
	if (a)
		tcsetattr(1, TCSANOW, &(g_bin->new_stdout));
	else
		tcsetattr(1, TCSANOW, &(g_bin->old_stdout));
}

void	init_termios(void)
{
	tcgetattr(1, &(g_bin->old_stdout));
	tcgetattr(1, &(g_bin->new_stdout));
	g_bin->old_stdout.c_lflag |= ECHOCTL;
	g_bin->new_stdout.c_lflag &= ~(ECHOCTL);
}

void	reset_subsystem(int pid, int a)
{
	reset_signal(pid);
	manage_termios(a);
}
