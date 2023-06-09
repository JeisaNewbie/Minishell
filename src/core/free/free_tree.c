/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:48:14 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:04 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirect(t_redirect *redirect)
{
	if (redirect->type)
		free_token(redirect->type);
	if (redirect->file_name)
		free_token(redirect->file_name);
	free(redirect);
}

void	free_redirects(t_redirects *redirects)
{
	if (redirects->redirect)
		free_redirect(redirects->redirect);
	if (redirects->redirects)
		free_redirects(redirects->redirects);
	free(redirects);
}

void	free_simple_cmd(t_simple_cmd *simple_cmd)
{
	if (simple_cmd->argv)
		free_deque_with_token(simple_cmd->argv);
	free(simple_cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->simple_cmd)
		free_simple_cmd(cmd->simple_cmd);
	if (cmd->redirects)
		free_redirects(cmd->redirects);
	free(cmd);
}

void	free_pipe(t_pipe *pipe)
{
	if (pipe->cmd)
		free_cmd(pipe->cmd);
	if (pipe->pipe)
		free_pipe(pipe->pipe);
	free(pipe);
}
