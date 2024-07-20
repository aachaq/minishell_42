/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abboutah <abboutah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:59:37 by abboutah          #+#    #+#             */
/*   Updated: 2023/02/10 12:59:37 by abboutah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/execution.h"
#include "../../libft/libft.h"
#include "../../include/lexer.h"

int	remove_token(t_list *token)
{
	t_list	*nextt;

	nextt = token->next->next;
	ft_lstdelone(token->next, delete_token);
	if (nextt == NULL)
	{
		ft_lstdelone(token, delete_token);
		return (0);
	}
	delete_token(token->content);
	token->content = nextt->content;
	token->next = nextt->next;
	free(nextt);
	return (1);
}

int	remove_tokens(t_list **token)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = *token;
	while (current)
	{
		while (((t_token *)current->content)->e_type >= token_red_input)
		{
			if (!remove_token(current))
			{
				if (previous == NULL)
					*token = NULL;
				else
					previous->next = NULL;
				return (*token != NULL);
			}
		}
		previous = current;
		current = current->next;
	}
	return (1);
}

int	o_file(const char	*file, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 1)
		fd = open(file, O_RDONLY, 0777);
	else if (i == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		if (i == 0 || i == 2)
			perror("Error");
		if (i == 2)
			exit(set_exit(errno));
		if (i == 1)
			erreur(1, (char *) file, NULL, "No such file or directory");
	}
	return (fd);
}

int	which_fd(t_list *token)
{
	t_token		*current;
	t_token		*next;
	int			r;

	r = 0;
	current = token->content;
	if (token->next == NULL)
		return (r);
	next = token->next->content;
	if (current->e_type < 2)
		return (r);
	if (current->e_type == token_red_input)
		r = o_file(next->value, 1);
	else if (current->e_type == token_herdoc)
	{
		r = o_file(next->value, 1);
		unlink(next->value);
	}
	else if (current->e_type == token_red_output)
		r = o_file(next->value, 2);
	else if (current->e_type == token_appand)
		r = o_file(next->value, 3);
	return (r);
}

int	fd_redirection(t_list **token)
{
	int		fd;
	t_list	*current;

	current = *token;
	while (current)
	{
		fd = which_fd(current);
		if (fd == -1)
			return (0);
		if (fd > 0)
		{
			if (((t_token *) current->content)->e_type == token_red_input || \
				((t_token *) current->content)->e_type == token_herdoc)
				dup2(fd, 0);
			else
				dup2(fd, 1);
			close(fd);
			current = current->next;
		}
		current = current->next;
	}
	return (remove_tokens(token));
}
