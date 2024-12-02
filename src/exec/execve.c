/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:04:14 by nkermani          #+#    #+#             */
/*   Updated: 2024/07/23 01:59:32 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "struct.h"
#include "utils.h"
#include <string.h>
#include <sys/stat.h>

static char	*fetch_in_env(char *str, char **envp)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = -1;
	while (envp && envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (sub == NULL)
			return (NULL);
		if (ft_strcmp(sub, str) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char **envp)
{
	size_t	i;
	char	*path;
	char	**dir_path_tab;
	char	**cmd_tab;
	char	*exec;

	cmd_tab = ft_split(cmd, ' ');
	i = -1;
	dir_path_tab = ft_split(fetch_in_env("PATH", envp), ':');
	while (dir_path_tab && dir_path_tab[++i])
	{
		path = ft_strjoin(dir_path_tab[i], "/");
		exec = ft_strjoin(path, *cmd_tab);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			exec_ft_free_tab(dir_path_tab);
			exec_ft_free_tab(cmd_tab);
			return (exec);
		}
		free(exec);
	}
	exec_ft_free_tab(dir_path_tab);
	exec_ft_free_tab(cmd_tab);
	return (ft_strdup(cmd));
}

static int	exec_ft_execve_end(char **envp, char ***split_cmd, char **path)
{
	struct stat	path_stat;

	if (execve((*split_cmd)[0], *split_cmd, envp) == -1)
	{
		*path = find_cmd_path((*split_cmd)[0], envp);
		if (execve(*path, *split_cmd, envp) == -1)
		{
			if (stat(*path, &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
					return (free(*path), exec_ft_free_tab(*split_cmd),
						ft_write(2, "Is a directory\n"), 126);
			}
			else
				return (free(*path), exec_ft_free_tab(*split_cmd),
					ft_write(2, "Command not found\n"), 127);
			perror("execve error");
			return (1);
		}
	}
	return (0);
}

static int	exec_ft_exec2(char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;

	if (!cmd)
		return (-1);
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
	{
		perror("split error");
		return (-1);
	}
	if (!split_cmd[0])
	{
		exec_ft_free_tab(split_cmd);
		ft_write(2, "invalid command\n");
		return (-1);
	}
	return (exec_ft_execve_end(envp, &split_cmd, &path));
}

int	exec_exec_ft_execve(char *cmd, t_cmd *current, char **envp)
{
	t_cmd	*curr;

	if (!current)
		return (-1);
	curr = current;
	if (curr->type == COMMAND)
		return (exec_ft_exec2(cmd, envp));
	return (0);
}
