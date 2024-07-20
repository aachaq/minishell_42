/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:48:29 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/19 14:11:20 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit_with_error(const char *str, int exit_flag)
{
	ft_putstr_fd("minishell: fail to allocate memory", 2);
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)str, 2);
	}
	ft_putchar_fd('\n', 2);
	exit(exit_flag);
}
