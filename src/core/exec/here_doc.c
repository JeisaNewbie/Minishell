/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:36:02 by sechung           #+#    #+#             */
/*   Updated: 2023/07/20 03:16:06 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mk_num(char *str, int num)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < 6)
	{
		if (i == 0)
		{
			str[13 + i++] = num / 100000 + '0';
			num %= 100000;
		}
		str[13 + i++] = num / (100000 / (j * 10)) + '0';
		num %= (100000 / (j * 10));
		j *= 10;
	}
}

char	*mk_filename(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	i = 0;
	exist = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
	}
	return (str);
}

void	rm_heredoc(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	exist = 0;
	i = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
		if (!exist)
			unlink (str);
	}
	free (str);
}

void	check_heredoc(t_process *proc, t_redirects *redirects)
{
	int		fd;

	fd = 0;
	while (redirects)
	{
		if (!ft_strcmp (redirects->redirect->type->content, "<<"))
		{
			fd = open (proc->heredoc_file[proc->fd_idx],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			write_str(redirects->redirect->file_name->content,
					fd, proc->envp);
		}
		redirects = redirects->redirects;
	}
}

void	mk_heredoc(t_process *proc)
{
	t_pipe	*pipe;

	set_herdoc_signal ();
	pipe = proc->pipe;
	while (pipe)
	{
		proc->heredoc_file[proc->fd_idx] = mk_filename();
		if (pipe->cmd->redirects)
			check_heredoc (proc, pipe->cmd->redirects);
		proc->fd_idx++;
		pipe = pipe->pipe;
	}
}
