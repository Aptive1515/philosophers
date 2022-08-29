/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:23:00 by aptive            #+#    #+#             */
/*   Updated: 2022/08/27 17:37:40 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_uspleet(t_data *data, int	time)
{
	int	i;

	i = gettime();
	pthread_mutex_lock(data->mutex_dead);
	while (!data->dead_philo)
	{
		pthread_mutex_unlock(data->mutex_dead);
		if (gettime() - i >= time)
			return ;
		usleep(100);
		pthread_mutex_lock(data->mutex_dead);
	}
	pthread_mutex_unlock(data->mutex_dead);
}

void	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		 msg(time - philo->time_begin, philo->nb, "has taken a fork");
		// printf("%i %i has taken a fork\n",
		// 	gettime() - philo->time_begin, philo->nb);
	pthread_mutex_unlock(data->mutex_dead);
}

void	eating(t_philo *philo, t_data *data)
{
	int	time;

	pthread_mutex_lock(data->mutex_dead);
	time = gettime();
	if (!data->dead_philo)
		msg(time - philo->time_begin, philo->nb, "is eating");
		// printf("%i %i is eating\n", time - philo->time_begin, philo->nb);
	philo->last_meal = time;
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->have_meal++;
	ft_uspleet(data, philo->time_to_eat);
	// usleep(philo->time_to_eat * 1000);
}

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		msg(time - philo->time_begin, philo->nb, "is sleeping");

		// printf("%i %i is sleeping\n", gettime() - philo->time_begin, philo->nb);
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	ft_uspleet(data, philo->time_to_sleep);

	// usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		msg(time - philo->time_begin, philo->nb, "is thinking");

		// printf("%i %i is thinking\n", gettime() - philo->time_begin, philo->nb);
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 1;
	philo->is_thinking = 0;
	// if (philo->nb % 2 != 0)
	// 	usleep(1 * 100);
}
