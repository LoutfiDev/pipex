/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:27:52 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/29 01:38:33 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>  
# include <stdlib.h>

char	*get_next_line(int fd);
int		gnl_strlen(char *str);
int		gnl_memchr(char *str, int c, int n);
char	*gnl_strdup(char *s1);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char *str, int start, int len);

#endif
