/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:36:03 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/22 09:36:46 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		close(data->pipes[i][READ_END]);
		close(data->pipes[i][WRITE_END]);
		i++;
	}
	close(data->infile);
	close(data->outfile);
	return ;
}

void	ft_free_array(char **array)
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

void	ft_free_pipes(int **pipes, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
		free(pipes[i++]);
	free(pipes);
	return ;
}

void	ft_free(t_data	*data)
{
	ft_close(data);
	ft_free_pipes(data->pipes, data->nbr_pipes);
	ft_free_array(data->cmd);
	free(data);
	return ;
}