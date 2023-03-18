/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:20:00 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/18 17:07:34 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void _fork1(t_data *data, int *p, char **env)
{
	pid_t id_ls;
	char	**array;
	char	*cmd;
	
	id_ls = fork();
	if (id_ls < 0)
		exit (ERROR);
	else if (id_ls == 0)
	{
		if(dup2(STDIN_FILENO, data->infile) == -1)
			exit (ERROR);
		if(dup2(p[WRITE_END], STDOUT_FILENO) == -1)
			exit (ERROR);
		close(p[0]);
		close(p[1]);
		array = ft_split(data->cmd[0], ' ');
		cmd = check_path(array[0], env);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

void	_fork2(t_data *data, int *p, char **env)
{
	pid_t id_grep;
	char	**array;
	char	*cmd;
	
	id_grep = fork();
	if (id_grep < 0)
		exit (ERROR);
	else if (id_grep == 0)
	{
		if(dup2(p[READ_END], STDIN_FILENO) == -1)
			exit(ERROR);
		if(dup2(STDOUT_FILENO, data->outfile) == -1)
			exit(ERROR);
		close(p[0]);
		close(p[1]);
		array = ft_split(data->cmd[1], ' ');
		cmd = check_path(array[0], env);
		execve(cmd, &array[0], env);
		exit (ERROR);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int p[2];

	check_args(ac, av, env, MANDATORY);
	data = _init(ac, av);
	if (!data)
		return (ERROR);
	if (pipe(p))
		return (1);
	_fork1(data, p, env);
	_fork2(data, p, env);
	close(p[0]);
	close(p[1]);
    while (wait(NULL) > 0);
	ft_free(data->cmd);
	ft_close(data);
	free(data);
	return (SUCCESS);
}
	// printf("%s\n", av[0]);
	// av++;
	// int i = execve(av[0], av, NULL);
	// printf("%d\n", i);