/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 14:17:59 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_etat_philo(t_philo *philo)
{
	printf("************************************\n");
	printf("Philo %i, eating %i, sleeping %i, think %i, dead %i, last meal %lli\n\n",
	 philo->nb, philo->is_eating, philo->is_spleeping, philo->is_thinking, philo->is_dead, philo->last_meal);
}

void	*ft_test(void *arg)
{
	t_data	*data;
	int		k;

	k = 0;
	data = arg;
	data->philo->time_begin = gettime();
	data->philo->last_meal = data->philo->time_begin;
	while (!data->dead_philo)
	{
		if (data->philo->is_eating)
		{
			if (!pthread_mutex_lock(data->fork_r))
				k++;
			if (!pthread_mutex_lock(data->fork_l))
				ft_eating(data->philo, data);
			if (!pthread_mutex_unlock(data->fork_r))
				k++;
			if (!pthread_mutex_unlock(data->fork_l))
				k++;
		}
		if (data->philo->is_spleeping)
			ft_sleeping(data->philo, data);
		if (data->philo->is_thinking)
			ft_thinking(data->philo, data);
	}
	return (arg);
}

void	ft_eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		ft_msg(gettime() - philo->time_begin , philo->nb, "is eating");
	}
		pthread_mutex_unlock(data->mutex_dead);
		philo->last_meal = gettime();
		usleep(philo->time_to_eat * 1000);
		philo->is_eating = 0;
		philo->is_spleeping = 1;
}

void	ft_sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		ft_msg(gettime() - philo->time_begin , philo->nb, "is sleeping");
	}
	pthread_mutex_unlock(data->mutex_dead);
	usleep(philo->time_to_sleep * 1000);
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
}

void	ft_thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		ft_msg(gettime() - philo->time_begin , philo->nb, "is thinking");
	}
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 1;
	philo->is_thinking = 0;
}
