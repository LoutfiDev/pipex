/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:43:24 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/14 10:25:21 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free(char **array)
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

char **init_cmd(int ac, char **av)
{
	char	**cmd;
	int		i;
	int		j;
	
	i = 2;
	j = 0;
	cmd  = ft_calloc(ac - 2, sizeof(char *));
	if (!cmd)	
		return (NULL);
	while (j < ac - 3)
		cmd[j++] = ft_strdup(av[i++]);
	return (cmd);
}

t_data	*_init(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return NULL;
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_CREAT);
	data->nbr_cmd = ac - 3;
	data->cmd = init_cmd(ac, av);
	if (!data->cmd)
		return (NULL);
	return (data);
}