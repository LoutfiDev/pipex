/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:27:56 by yloutfi           #+#    #+#             */
/*   Updated: 2022/11/12 12:47:26 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_memchr(char *str, int c, int n)
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

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;

	if (!s1)
		return (NULL);
	ptr = (char *)malloc(ft_strlen(s1) + 1);
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

char	*ft_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	if (!str)
		return (0);
	if (start + len > ft_strlen(str))
		len = ft_strlen(str) - start;
	if (start >= ft_strlen(str))
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	int		lenght;
	char	*res;

	if (!s1 || !s1[0])
		return (ft_strdup(s2));
	if (!s2 || !s2[0])
		return (NULL);
	lenght = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((lenght + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	lenght = 0;
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && i < len)
		res[lenght++] = s1[i++];
	len = ft_strlen(s2);
	i = 0;
	while (s2[i] && i < len)
		res[lenght++] = s2[i++];
	res[lenght] = '\0';
	free(s1);
	return (res);
}
