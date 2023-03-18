/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:43:24 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/18 17:04:05 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	data->outfile = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
	data->nbr_cmd = ac - 3;
	data->cmd = init_cmd(ac, av);
	if (!data->cmd)
		return (NULL);
	return (data);
}