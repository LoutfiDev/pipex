/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:20:00 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/14 10:25:37 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av)
{
	t_data	*data;
	
	check_args(ac, av, 0);
	data = _init(ac, av);
	if (!data)
		return (ERROR);
	ft_free(data->cmd);
	free(data);
	return (SUCCESS);
}