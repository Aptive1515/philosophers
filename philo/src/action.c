/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:23:00 by aptive            #+#    #+#             */
/*   Updated: 2022/08/22 18:25:02 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		printf("%i %i has taken a fork\n", gettime() - philo->time_begin, philo->nb);
		// msg(gettime() - philo->time_begin, philo->nb, "has taken a fork");
		// msg(gettime() - philo->time_begin, philo->nb, "has taken a fork");
	}
	pthread_mutex_unlock(data->mutex_dead);
}

void	eating(t_philo *philo, t_data *data)
{
	int time;

	pthread_mutex_lock(data->mutex_dead);
	time = gettime();
	if (!data->dead_philo)
		printf("%i %i is eating\n", time - philo->time_begin, philo->nb);
		// msg(time - philo->time_begin, philo->nb, "is eating");
	philo->last_meal = time;
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->have_meal++;
	usleep(philo->time_to_eat * 1000);
}

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		printf("%i %i is spleeping\n", gettime() - philo->time_begin, philo->nb);
		// msg(gettime() - philo->time_begin, philo->nb, "is sleeping");
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		printf("%i %i is thinking\n", gettime() - philo->time_begin, philo->nb);
		// msg(gettime() - philo->time_begin, philo->nb, "is thinking");
	pthread_mutex_unlock(data->mutex_dead);
	philo->is_eating = 1;
	philo->is_thinking = 0;
	usleep(1 * 1000);
}
