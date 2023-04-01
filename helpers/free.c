/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:36:03 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/01 01:27:58 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipe)
	{
		close(data->pipe[i][READ_END]);
		close(data->pipe[i][WRITE_END]);
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

void	ft_free_pipe(int **pipe, int nbr_pipe)
{
	int	i;

	i = 0;
	while (i < nbr_pipe)
		free(pipe[i++]);
	free(pipe);
	return ;
}

void	ft_free(t_data	*data)
{
	ft_close(data);
	ft_free_pipe(data->pipe, data->nbr_pipe);
	ft_free_array(data->cmd);
	free(data);
	return ;
}
