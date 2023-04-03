/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:15:11 by yloutfi           #+#    #+#             */
/*   Updated: 2023/04/02 18:12:03 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_nbr_array(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == 0)
		return (0);
	if (str[0] != c && str[0])
		count++;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			count++;
		i++;
	}
	return (count);
}

static char	*ft_fill_array(const char *str, char c, int *j)
{
	int		start;
	int		length;

	start = *j;
	length = 0;
	while (str[*j] != c && str[*j])
	{
		(*j)++;
		length++;
	}
	return (ft_substr(str, start, length));
}

static char	**ft_free_array_tab(char **big_array)
{
	int	i;

	i = 0;
	while (big_array[i])
	{
		free(big_array[i]);
		i++;
	}
	free(big_array);
	return (NULL);
}

char	**check_space(char const *s)
{
	char	**big_array;

	big_array = ft_calloc((2), sizeof(char *));
	if (big_array == NULL)
		return (0);
	if (s[0] == ' ' || s[ft_strlen(s) - 1] == ' ')
	{
		big_array[0] = ft_strdup(s);
		return (big_array);
	}
	free(big_array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**big_array;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	j = 0;
	big_array = check_space(s);
	if (big_array)
		return (big_array);
	nbr = ft_nbr_array(s, c);
	big_array = ft_calloc((nbr + 1), sizeof(char *));
	if (big_array == NULL)
		return (0);
	while (s && i < nbr)
	{
		while (s[j] && s[j] == c)
			j++;
		big_array[i++] = ft_fill_array(s, c, &j);
		if (!big_array[i - 1])
			return (ft_free_array_tab(big_array));
		j++;
	}
	return (big_array);
}
