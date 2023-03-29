/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:55:02 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/29 01:44:37 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	length = 0;
	if (dst)
		length = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= length)
		return (len + dstsize);
	while (src[i] && i < dstsize - length - 1)
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (length + len);
}
