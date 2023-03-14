/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:44:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/14 10:23:46 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int isfile_exist(char *filename)
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

int iscmd_exist(char *cmd)
{
	char	**array;
	char	*path;
	int		status;
	int		exit_code;
	
	exit_code = SUCCESS;
	array = ft_split(cmd, ' ');
	path = ft_strjoin("/bin/", array[0]);
	status = access(path, F_OK);
	if (status == -1)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(array[0], 2);
		ft_putstr_fd("\n", 2);
		exit_code = ERROR;
	}
	ft_free(array);
	free(path);
	return (exit_code);
}

void check_args(int ac, char **av, int bonus)
{
	int	i;
	int	status;

	status = SUCCESS;
	i = 2;
	if (!(ac == 5) && !bonus)
	{
		ft_putstr_fd("Error: too few/many arguments\n", 2);
		status = ERROR;	
	}
	if (ac < 5 && bonus)
	{
		ft_putstr_fd("Error: too few arguments\n", 2);
		status = ERROR;
	}
	if (isfile_exist(av[1]))
		status = ERROR;
	while (i < ac - 1)
		if (iscmd_exist(av[i++]))
			status = ERROR;
	i = open(av[ac - 1], O_CREAT);
	close(i);
	if (status)
		exit(ERROR);
}
