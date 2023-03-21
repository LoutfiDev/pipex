/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:12:22 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/21 21:21:48 by yloutfi          ###   ########.fr       */
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
# define MANDATORY 0
# define BONUS 1
# define READ_END 0
# define WRITE_END 1

//define structs
typedef struct s_data
{
	int		infile;
	int		outfile;
	int		nbr_cmd;
	char	**cmd;
	int		nbr_pipes;
	int		**pipes;
}	t_data;

//helpers functions
void	ft_free(t_data	*data);
void	ft_free_array(char **array);
char	*get_path(char **env);
char	*join_path(char *cmd, char **env);

//parse functions
void	check_args(int ac, char **av, char **env, int bonus);

//initialize functions 
t_data	*_init(int ac, char **av);

#endif