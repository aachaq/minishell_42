/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:59 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/21 12:32:38 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>

//cd
int		cd(t_list *token, int fd);
//echo
int		echo(t_list *token, int fd);
//export
int		check_var(const char *var);
int		ft_export(char *var);
int		export(t_list *token, int fd);
//env
t_list	*ft_env(const char *value);
int		init_env(int ac, char **av, char **env);
int		env(t_list *token, int fd);
//exit
int		set_exit(int status);
int		ft_exit(t_list *token, int fd);
//unset
int		unset(t_list *token, int fd);
//pwd
int		pwd(t_list *token, int fd);
//utils
int		erreur(int status, char *cmd, char *arg, char *d_error);
char	*get_home(void);
char	*ft_getcwd(void);
char	*get_oldpwd(void);
int		get_path(char **path);
char	*relative_path(char *path);
char	*absolute_path(char *path);

typedef struct termios	t_termios;

typedef struct s_bin
{
	t_list		*token;
	t_list		*env;
	t_list		*cmd;
	t_list		**leaks;
	t_termios	old_stdout;
	t_termios	new_stdout;
	int			exp_herdoc;
	int			exit_status;
	int			lexer_erreur;
	int			o_fd[3];
	int			fd[2];
	int			result;
	int			i_memoir;
}					t_bin;

t_bin					*g_bin;

#endif