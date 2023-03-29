/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:22:37 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/29 01:44:37 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{	
	char	*d;
	char	*s;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d > s)
	{
		while (len > 0)
		{
			len --;
			d[len] = s[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
