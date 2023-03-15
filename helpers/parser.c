/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:44:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/15 09:30:38 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	isfile_exist(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	iscmd_exist(char *cmd, char **env)
{
	char	**array;
	char	*path;
	int		status;
	int		i;

	i = 0;
	array = ft_split(get_path(env), ':');
	while (array[i])
	{
		path = ft_strjoin(array[i++], "/", cmd);
		status = access(path, F_OK);
		free(path);
		if (status != -1)
			break ;
	}
	ft_free(array);
	if (status == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void	check_args(int ac, char **av, char **env, int bonus)
{
	char	**cmd;
	int		status;
	int		i;

	status = SUCCESS;
	i = 2;
	if ((!(ac == 5) && !bonus) || (ac < 5 && bonus))
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		exit(ERROR);
	}
	if (isfile_exist(av[1]))
		status = ERROR;
	while (i < ac - 1)
	{
		cmd = ft_split(av[i++], ' ');
		if (iscmd_exist(cmd[0], env))
			status = ERROR;
		ft_free(cmd);
	}
	i = open(av[ac - 1], O_CREAT);
	close(i);
	if (status)
		exit(ERROR);
}
