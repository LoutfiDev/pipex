/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:20:00 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/18 11:08:27 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	check_args(ac, av, env, MANDATORY);
	data = _init(ac, av);
	if (!data)
		return (ERROR);
	ft_free(data->cmd);
	ft_close(data);
	free(data);
	while(1);
	return (SUCCESS);
}
	// printf("%s\n", av[0]);
	// av++;
	// int i = execve(av[0], av, NULL);
	// printf("%d\n", i);