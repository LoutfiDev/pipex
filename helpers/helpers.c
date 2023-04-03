/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:08:05 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/03 02:47:10 by yloutfi          ###   ########.fr       */
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
		if (array[0][0] != '/')
			cmd = join_path(array[0], env);
		else
			cmd = ft_strdup(array[0]);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

void	tmp_heredoc(char *limiter, int *heredoc)
{
	char	*list;
	char	*tmp;
	char	*temp;

	if (*heredoc > 0)
		return ;
	temp = ft_strdup(limiter);
	tmp = gnl_strjoin(temp, "\n");
	while (1)
	{
		write(STDIN_FILENO, "heredoc>", ft_strlen("heredoc>"));
		list = get_next_line(STDIN_FILENO);
		if (!list || ft_strcmp(list, tmp) == 0)
			break ;
		free(list);
	}
	*heredoc += 1;
	free(list);
	free(tmp);
	return ;
}

int	iscmd_exist_herdoc(char *cmd, char **env, char *limiter, int *heredoc)
{
	char	*path;
	int		status;

	if (!(cmd[0] >= 'A' && cmd[0] <= 'Z') && !(cmd[0] >= 'a' && cmd[0] <= 'z'))
	{
		status = access(cmd, F_OK);
		if (status == -1)
			path = NULL;
		else
			path = ft_strdup(cmd);
	}
	else
		path = join_path(cmd, env);
	if (!path)
	{
		tmp_heredoc(limiter, heredoc);
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (ERROR);
	}
	free(path);
	return (SUCCESS);
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
