/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:12:22 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/02 18:34:53 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../includes/libft.h"
# include "../includes/get_next_line.h"

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
	int		nbr_pipe;
	int		**pipe;
}	t_data;

//helpers functions
char	*get_path(char **env);
char	*join_path(char *cmd, char **env);
void	_fork(t_data *data, int i, int j, char **env);
void	tmp_heredoc(char *limiter, int *heredoc);
int		iscmd_exist_herdoc(char *cmd, char **env, char *limiter, int *heredoc);
int		is_empty(int ac, char **av, int heredoc);

//parse functions
void	check_args(int ac, char **av, char **env, int bonus);
int		check_heredoc(int ac, char **av, char **env);

//free functions 
void	ft_free(t_data	*data);
void	ft_close(t_data *data);
void	ft_free_array(char **array);

//initialize functions 
t_data	*_init(int ac, char **av);
t_data	*_init_heredoc(int ac, char **av);

#endif