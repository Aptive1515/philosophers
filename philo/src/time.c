/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:58:06 by aptive            #+#    #+#             */
/*   Updated: 2022/08/27 17:36:02 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	gettime(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((int)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	msg(int time, int philo_nb, char *str)
{
	ft_putnbr_fd((int)time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo_nb, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}
