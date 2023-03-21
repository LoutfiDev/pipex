/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:20:00 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/21 09:33:32 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	_fork1(t_data *data, int *p, char **env)
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
		if (dup2(p[WRITE_END], STDOUT_FILENO) == -1)
			exit (ERROR);
		close(p[READ_END]);
		close(p[WRITE_END]);
		array = ft_split(data->cmd[0], ' ');
		cmd = join_path(array[0], env);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

void	_fork2(t_data *data, int *p, char **env)
{
	pid_t	id_grep;
	char	**array;
	char	*cmd;

	id_grep = fork();
	if (id_grep < 0)
		exit (ERROR);
	else if (id_grep == 0)
	{
		if (dup2(p[READ_END], STDIN_FILENO) == -1)
			exit(ERROR);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			exit(ERROR);
		close(p[READ_END]);
		close(p[WRITE_END]);
		array = ft_split(data->cmd[1], ' ');
		cmd = join_path(array[0], env);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		p[2];

	check_args(ac, av, env, MANDATORY);
	data = _init(ac, av);
	if (!data)
		return (ERROR);
	if (pipe(p))
		return (1);
	_fork1(data, p, env);
	_fork2(data, p, env);
	close(p[READ_END]);
	close(p[WRITE_END]);
	while (wait(NULL) != -1)
		;
	ft_free(data->cmd);
	ft_close(data);
	free(data);
	return (SUCCESS);
}
