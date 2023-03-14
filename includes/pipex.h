/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:12:22 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/14 10:24:27 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

//fotr test only
# include <stdio.h>

//define MACROS
# define SUCCESS 0
# define ERROR 1

//define structs
typedef struct s_data
{
	int		infile;
	int 	outfile;
	int		nbr_cmd;
	char	**cmd;
}	t_data;

//helpers functions
void	ft_free(char **array);

//parse functions
void 	check_args(int ac, char **av, int bonus);

//initialize functions 
t_data	*_init(int ac, char **av);

#endif