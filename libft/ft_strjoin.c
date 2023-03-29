/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:45:57 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/29 01:44:37 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	char	*res;
	char	*q;

	if (!s1 || !s2 || !s3)
		return (0);
	q = malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (q == NULL)
		return (0);
	res = q;
	i = 0;
	while (s1[i] && i < ft_strlen(s1))
		*res++ = s1[i++];
	i = 0;
	while (s2[i] && i < ft_strlen(s2))
		*res++ = s2[i++];
	i = 0;
	while (s3[i] && i < ft_strlen(s3))
		*res++ = s3[i++];
	*res = '\0';
	return (q);
}
