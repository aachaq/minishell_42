/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:00:06 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 13:00:06 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

//signal
int		init_signal(void);
int		reset_signal(int pid);
void	signal_heredoc(int pid);
//termios
void	init_termios(void);
void	manage_termios(int a);
void	reset_subsystem(int pid, int a);

#endif