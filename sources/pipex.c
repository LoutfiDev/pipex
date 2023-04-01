/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:20:00 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/01 02:45:18 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	_fork1(t_data *data, char **env)
{
	pid_t	id_ls;
	char	**array;
	char	*cmd;

	id_ls = fork();
	if (id_ls < 0)
		exit (ERROR);
	else if (id_ls == 0)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			exit (ERROR);
		if (dup2(data->pipe[0][WRITE_END], STDOUT_FILENO) == -1)
			exit (ERROR);
		close(data->pipe[0][READ_END]);
		close(data->pipe[0][WRITE_END]);
		array = ft_split(data->cmd[0], ' ');
		if (array[0][0] != '/')
			cmd = join_path(array[0], env);
		else
			cmd = ft_strdup(array[0]);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

void	_fork2(t_data *data, char **env)
{
	pid_t	id_grep;
	char	**array;
	char	*cmd;

	id_grep = fork();
	if (id_grep < 0)
		exit (ERROR);
	else if (id_grep == 0)
	{
		if (dup2(data->pipe[0][READ_END], STDIN_FILENO) == -1)
			exit(ERROR);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			exit(ERROR);
		close(data->pipe[0][READ_END]);
		close(data->pipe[0][WRITE_END]);
		array = ft_split(data->cmd[1], ' ');
		if (array[0][0] != '/')
			cmd = join_path(array[0], env);
		else
			cmd = ft_strdup(array[0]);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	check_args(ac, av, env, MANDATORY);
	data = _init(ac, av);
	if (!data)
		return (ERROR);
	_fork1(data, env);
	_fork2(data, env);
	ft_free(data);
	while (wait(NULL) != -1)
		;
	return (SUCCESS);
}
