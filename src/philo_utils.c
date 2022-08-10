/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:10:26 by tdelauna          #+#    #+#             */
/*   Updated: 2022/08/10 12:05:29 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_free_all(t_data *(*data))
{
	int	i;

	i = 0;
	free(data[i]->to_print);
	free(data[i]->mutex_dead);
	while (data[i])
	{
		free(data[i]->fork_l);
		free(data[i]->philo);
		free(data[i]);
		i++;
	}
	free(data);
}

int	ft_philo_dead(t_data *(*data))
{
	int	i;
	int	j;

	i = 0;
	usleep(200000);
	while (data[i])
	{
		if ((gettime() - data[i]->philo->last_meal) >= (unsigned long long)data[i]->philo->time_to_die)
			ft_died(data[i]->philo, data[i]);
		if (!pthread_mutex_lock(data[i]->mutex_dead))
		{
			if (data[i]->dead_philo)
			{
				j = -1;
				while (data[++j])
				{
					data[j]->dead_philo = 1;
				}
				pthread_mutex_unlock(data[i]->mutex_dead);
				return (0);
			}
			pthread_mutex_unlock(data[i]->mutex_dead);
		}
		i++;
	}
	return (1);
}

void	ft_died(t_philo *philo, t_data *data)
{
	(void)data;
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		ft_msg(gettime() - philo->time_begin , philo->nb, "died");
	data->dead_philo = 1;
	pthread_mutex_unlock(data->mutex_dead);
}

void	ft_msg( int time ,int philo_nb, char* str)
{
	// ft_printf("%l %d is eating\n", (gettime() - philo->time_begin), philo->nb);
	ft_putnbr_fd((int)time, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(philo_nb, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}
