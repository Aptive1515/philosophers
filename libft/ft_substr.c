/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:30:08 by tdelauna          #+#    #+#             */
/*   Updated: 2021/12/08 15:25:47 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		len = 0;
	/*else if (len > ft_strlen(s))
		len = ft_strlen(s);*/
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	dest[len] = '\0';
	return (dest);
}
