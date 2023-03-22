/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:08:05 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/22 09:36:50 by yloutfi          ###   ########.fr       */
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
