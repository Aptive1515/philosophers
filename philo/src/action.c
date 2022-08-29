/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:23:00 by aptive            #+#    #+#             */
/*   Updated: 2022/08/29 17:56:34 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_uspleet(t_data *data, int time)
{
	int	i;

	i = gettime();
	pthread_mutex_lock(data->mutex_dead);
	while (!data->dead_philo)
	{
		pthread_mutex_unlock(data->mutex_dead);
		if (gettime() - i >= time)
			return ;
		usleep(250);
		pthread_mutex_lock(data->mutex_dead);
	}
	pthread_mutex_unlock(data->mutex_dead);
}

void	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		printf("%i %i has taken a fork\n", gettime() - philo->time_begin,
			philo->nb);
		pthread_mutex_unlock(data->mutex_dead);
	}
	else
		pthread_mutex_unlock(data->mutex_dead);
}

void	eating(t_philo *philo, t_data *data)
{
	int	time;

	pthread_mutex_lock(data->mutex_dead);
	time = gettime();
	if (!data->dead_philo)
	{
		philo->last_meal = time;
		printf("%i %i is eating\n", gettime() - philo->time_begin, philo->nb);
		pthread_mutex_unlock(data->mutex_dead);
	}
	else
		pthread_mutex_unlock(data->mutex_dead);
	philo->have_meal++;
	ft_uspleet(data, philo->time_to_eat);
}

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		printf("%i %i is sleeping\n", gettime() - philo->time_begin, philo->nb);
		pthread_mutex_unlock(data->mutex_dead);
	}
	else
		pthread_mutex_unlock(data->mutex_dead);
	ft_uspleet(data, philo->time_to_sleep);
	thinking(data->philo, data);
}

void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		printf("%i %i is thinking\n", gettime() - philo->time_begin, philo->nb);
		pthread_mutex_unlock(data->mutex_dead);
	}
	else
		pthread_mutex_unlock(data->mutex_dead);
	usleep(50);
}
