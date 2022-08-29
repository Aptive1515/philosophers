/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:09:57 by tdelauna          #+#    #+#             */
/*   Updated: 2022/08/29 15:14:00 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*a;

	a = (char *)s;
	i = 0;
	while (i < n)
		a[i++] = '\0';
	return (s);
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;

	ptr = malloc(elementCount * elementSize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, elementCount * elementSize);
	return (ptr);
}

int	ft_itoa_size(int n)
{
	int	size;

	size = 0;
	if (n < 0 && n > -2147483648)
	{
		size++;
		n = -n;
	}
	else if (n == 0)
	{
		return (1);
	}
	else if (n == -2147483648)
	{
		return (11);
	}
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	unsigned int	tmp;

	size = ft_itoa_size(n);
	tmp = n;
	if (n < 0)
		tmp = -n;
	i = 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (tmp == 0)
		str[tmp] = '0';
	while (tmp >= 1)
	{
		str[size - i++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (n < 0)
		*str = '-';
	str[size] = '\0';
	return (str);
}
