/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:27:56 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/03 02:46:39 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	gnl_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	gnl_memchr(char *str, int c, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*gnl_strdup(char *s1)
{
	char	*ptr;
	int		i;

	if (!s1)
		return (NULL);
	ptr = (char *)malloc(gnl_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*gnl_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	if (!str)
		return (0);
	if (start + len > gnl_strlen(str))
		len = gnl_strlen(str) - start;
	if (start >= gnl_strlen(str))
		return (NULL);
	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (0);
	while (str[i] && i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*final_str;
	int		total_len;
	int		i;

	i = 0;
	total_len = gnl_strlen(s1) + gnl_strlen(s2);
	final_str = malloc(sizeof(char) * (total_len + 1));
	if (!final_str)
		return (0);
	if (!s1)
		s1 = gnl_strdup("");
	if (s1)
		ft_strcpy(final_str, s1);
	i = gnl_strlen(final_str);
	if (s2)
		ft_strcpy(final_str + i, s2);
	free(s1);
	return (final_str);
}
