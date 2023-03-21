/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:08:05 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/21 21:47:54 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		close(data->pipes[i][READ_END]);
		close(data->pipes[i][WRITE_END]);
		i++;
	}
	close(data->infile);
	close(data->outfile);
	return ;
}

void	ft_free_array(char **array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (array[len])
		len++;
	while (i <= len)
		free(array[i++]);
	free(array);
	return ;
}

void	ft_free_pipes(int **pipes, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
		free(pipes[i++]);
	free(pipes);
	return ;
}

void	ft_free(t_data	*data)
{
	ft_close(data);
	ft_free_pipes(data->pipes, data->nbr_pipes);
	ft_free_array(data->cmd);
	free(data);
	return ;
}

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
		//must free here
	}
	return (NULL);
}
