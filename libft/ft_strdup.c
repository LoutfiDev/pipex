/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:35:58 by yloutfi           #+#    #+#             */
/*   Updated: 2023/03/29 01:44:37 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	char	*q;

	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	q = ptr;
	while (*s1)
	{
		*q = *s1;
		q++;
		s1++;
	}
	*q = '\0';
	return (ptr);
}
