/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:08:05 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/22 13:43:23 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char **env)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			tmp = env[i];
		i++;
	}
	path = ft_strchr(tmp, '=');
	if (!path)
		return (NULL);
	return (path + 1);
}

void	_fork(t_data *data, int i, int j, char **env)
{
	pid_t	id_cmd;
	char	**array;
	char	*cmd;

	id_cmd = fork();
	if (id_cmd < 0)
		exit (ERROR);
	else if (id_cmd == 0)
	{
		if (dup2(data->pipe[j][READ_END], STDIN_FILENO) == -1)
			exit (ERROR);
		if (dup2(data->pipe[j + 1][WRITE_END], STDOUT_FILENO) == -1)
			exit (ERROR);
		ft_close(data);
		array = ft_split(data->cmd[i], ' ');
		cmd = join_path(array[0], env);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

char	*join_path(char *cmd, char **env)
{
	char	**array;
	char	*path;
	int		status;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	status = access(cmd, F_OK);
	if (status != -1)
		return (ft_strdup(cmd));
	array = ft_split(get_path(env), ':');
	while (array[i])
	{
		path = ft_strjoin(array[i++], "/", cmd);
		status = access(path, F_OK);
		if (status != -1)
		{
			ft_free_array(array);
			return (path);
		}
		free(path);
	}
	ft_free_array(array);
	return (NULL);
}
