/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:14:54 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/01 02:45:12 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_fork(t_data *data, char **env)
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
		ft_close(data);
		array = ft_split(data->cmd[0], ' ');
		if (array[0][0] != '/')
			cmd = join_path(array[0], env);
		else
			cmd = ft_strdup(array[0]);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

void	middle_forks(t_data *data, char **env)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < data->nbr_cmd - 1)
		_fork(data, i++, j++, env);
}

void	last_fork(t_data *data, char **env)
{
	pid_t	id_grep;
	char	**array;
	char	*cmd;

	id_grep = fork();
	if (id_grep < 0)
		exit (ERROR);
	else if (id_grep == 0)
	{
		if (dup2(data->pipe[data->nbr_pipe - 1][READ_END], STDIN_FILENO) == -1)
			exit(ERROR);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			exit(ERROR);
		ft_close(data);
		array = ft_split(data->cmd[data->nbr_cmd - 1], ' ');
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

	if (check_heredoc(ac, av, env))
	{
		check_args(ac, av, env, BONUS);
		data = _init(ac, av);
	}
	else
		data = _init_heredoc(ac, av);
	if (!data)
		return (ERROR);
	first_fork(data, env);
	middle_forks(data, env);
	last_fork(data, env);
	ft_free(data);
	while (wait(NULL) != -1)
		;
	return (SUCCESS);
}
