/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:43:24 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/03 15:17:06 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**init_cmd(int nbr_cmd, char **av)
{
	char	**cmd;
	int		i;
	int		j;

	i = 2;
	j = 0;
	cmd = ft_calloc(nbr_cmd + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (j < nbr_cmd)
	{
		cmd[j] = ft_strdup(av[i++]);
		if (!cmd[j])
		{
			free(cmd);
			return (NULL);
		}
		j++;
	}
	return (cmd);
}

int	**_init_pipe(int nbr)
{
	int	**p;
	int	i;

	i = 0;
	p = ft_calloc(sizeof(int *), nbr);
	if (!p)
		return (NULL);
	while (i < nbr)
	{
		p[i] = ft_calloc(sizeof(int), 2);
		if (!p[i])
		{
			free(p);
			return (NULL);
		}
		if (pipe(p[i]))
		{
			free(p);
			return (NULL);
		}
		i++;
	}
	return (p);
}

t_data	*_init(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (NULL);
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_TRUNC);
	if (data->outfile == -1)
	{
		ft_putstr_fd("Error: permission denied: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
	}
	data->nbr_cmd = ac - 3;
	data->cmd = init_cmd(data->nbr_cmd, av);
	if (!data->cmd)
		return (NULL);
	data->nbr_pipe = ac - 4;
	data->pipe = _init_pipe(data->nbr_pipe);
	if (!data->pipe)
		return (NULL);
	return (data);
}

void	heredoc(int fd, char *limiter)
{
	char	*list;
	char	*tmp;
	char	*temp;

	temp = ft_strdup(limiter);
	tmp = gnl_strjoin(temp, "\n");
	while (1)
	{
		write(STDIN_FILENO, "heredoc>", ft_strlen("heredoc>"));
		list = get_next_line(STDIN_FILENO);
		if (!list || ft_strcmp(list, tmp) == 0)
			break ;
		ft_putstr_fd(list, fd);
		free(list);
	}
	free(list);
	free(tmp);
	close(fd);
	return ;
}

t_data	*_init_heredoc(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (NULL);
	data->outfile = open(av[ac - 1], O_WRONLY | O_APPEND);
	if (data->outfile == -1)
	{
		ft_putstr_fd("Error: permission denied: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
	}
	data->nbr_pipe = ac - 5;
	data->nbr_cmd = ac - 4;
	data->cmd = init_cmd(data->nbr_cmd, av + 1);
	if (!data->cmd)
		return (NULL);
	data->pipe = _init_pipe(data->nbr_pipe);
	if (!data->pipe)
		return (NULL);
	data->infile = data->pipe[0][WRITE_END];
	heredoc(data->infile, av[2]);
	return (data);
}
