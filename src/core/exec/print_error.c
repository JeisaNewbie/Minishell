/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:39:36 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:17:57 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_error(char *path, char *home, int opt_flag)
{
	struct stat	file;

	if (!path && !home && opt_flag == 1)
		print_error ("cd", path, 4);
	else if (!path && !home && opt_flag == 2)
		print_error ("cd", path, 5);
	else if (stat(path, &file) == ERROR)
	{
		if (errno == ENOENT)
			print_error ("cd", path, 0);
	}
	else if ((file.st_mode & S_IFMT) != S_IFDIR)
		print_error ("cd", path, 3);
	g_exit_status = 1;
}

void	print_error(const char *cmd, char *option, int flags)
{
	char	*tmp;
	char	*str;

	str = ft_strdup (cmd);
	tmp = str;
	str = m_strjoin ("minishell: ", str);
	free (tmp);
	if (option)
	{
		tmp = str;
		str = m_strjoin (str, ": ");
		free (tmp);
		tmp = str;
		str = m_strjoin (str, option);
		free (tmp);
	}
	print_errortype (str, flags);
}

void	print_errortype(char *str, int flags)
{
	char	*tmp;

	tmp = str;
	if (flags == 0)
		str = m_strjoin (str, ": No such file or directory\n");
	else if (flags == 1)
		str = m_strjoin (str, ": command not found\n");
	else if (flags == 2)
		str = m_strjoin (str, ": not a valid identifier\n");
	else if (flags == 3)
		str = m_strjoin (str, ": Not a directory\n");
	else if (flags == 4)
		str = m_strjoin (str, ": HOME not set\n");
	else if (flags == 5)
		str = m_strjoin (str, ": OLDPWD not set\n");
	free (tmp);
	write (2, str, ft_strlen (str));
	free (str);
}
