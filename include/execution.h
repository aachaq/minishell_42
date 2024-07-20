/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:00:03 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 13:00:03 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "builtin.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

//execution
int		execute(void);
//external cmd
int		external(t_list *token);
//redirection
int		fd_redirection(t_list **token);
int		o_file(const char	*file, int i);
//utils
int		check_builtin(t_list *token);
int		execute_builtin(t_list *token, int fd);
int		set_underscore(void);
char	**ft_get_env(void);
void	delete_token(void *content);

#endif