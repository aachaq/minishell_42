/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:40:55 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/14 08:40:55 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/parser.h"
#include "../../include/lexer.h"
#include "../../include/execution.h"
#include "../../include/main.h"

char	*tmp_file(void)
{
	char		*r;
	char		*st;
	t_list		*tmp;
	static int	a;

	tmp = g_bin->env;
	r = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "TMPDIR= ", 7))
			r = ft_strdup(tmp->content + 7);
		tmp = tmp->next;
	}
	if (r == NULL)
		ft_strdup("/");
	ft_strcat(&r, ".heredoc");
	a++;
	st = ft_itoa(a);
	ft_strcat(&r, st);
	free (st);
	return (r);
}

void	ft_expand(char **line)
{
	char		*x;
	char		*r;
	char		*tmp;

	x = ft_strchr(*line, '$');
	if (!x)
		return ;
	r = ft_substr(*line, 0, x - *line);
	tmp = expand(x);
	ft_strcat(&r, tmp);
	free(tmp);
	free(*line);
	*line = r;
}

int	here_document(char *file, char *delimiter)
{
	int		fd;
	char	*line;

	fd = o_file(file, 0);
	if (fd == -1)
		return (set_exit(errno) == 0);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || !ft_strcmp(line, delimiter))
			break ;
		ft_expand(&line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	close(fd);
	return (1);
}

int	child_here_doc(t_token *token)
{
	char	*tmp_file_n;
	char	*delimiter;
	pid_t	pid;

	tmp_file_n = tmp_file();
	delimiter = ft_strdup(token->value);
	free(token->value);
	token->value = tmp_file_n;
	pid = fork();
	if (pid == -1)
	{
		free(delimiter);
		return (errno);
	}
	signal_heredoc(pid);
	if (pid == 0)
	{
		if (here_document(token->value, delimiter) == 0)
			exit(errno);
		exit(0);
	}
	free(delimiter);
	waitpid(pid, &g_bin->exit_status, 0);
	return (g_bin->exit_status);
}
