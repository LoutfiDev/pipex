/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:44:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/03 15:35:40 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	isinfile_exist(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && !access(filename, F_OK))
	{
		ft_putstr_fd("Error: permission denied: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	else if (fd == -1)
	{
		ft_putstr_fd("Error: No such file or directory: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

void	handle_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(ERROR);
	}
	close(fd);
	return ;
}

int	iscmd_exist(char *cmd, char **env)
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
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (ERROR);
	}
	free(path);
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
	if (is_empty(ac, av, 0))
		exit(ERROR);
	if (isinfile_exist(av[1]))
		status = ERROR;
	while (i < ac - 1)
	{
		cmd = ft_split(av[i++], ' ');
		if (iscmd_exist(cmd[0], env))
			status = ERROR;
		ft_free_array(cmd);
	}
	handle_outfile(av[ac - 1]);
}

int	check_heredoc(int ac, char **av, char **env)
{
	char	**cmd;
	int		status;
	int		i;
	int		heredoc;

	status = SUCCESS;
	heredoc = 0;
	i = 3;
	if (ac < 6)
		return (ERROR);
	if (is_empty(ac, av, 1))
		exit(ERROR);
	if (ft_strcmp(av[1], "here_doc"))
		return (ERROR);
	while (i < ac - 1)
	{
		cmd = ft_split(av[i++], ' ');
		if (iscmd_exist_herdoc(cmd[0], env, av[2], &heredoc))
			status = ERROR;
		ft_free_array(cmd);
	}
	handle_outfile(av[ac - 1]);
	if (status)
		exit(ERROR);
	return (SUCCESS);
}
