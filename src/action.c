/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:23:00 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 19:13:58 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		msg(gettime() - philo->time_begin, philo->nb, "has taken a fork");
		msg(gettime() - philo->time_begin, philo->nb, "has taken a fork");
	}
	pthread_mutex_unlock(data->mutex_dead);
}

void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		msg(gettime() - philo->time_begin, philo->nb, "is eating");
	}
	philo->last_meal = gettime();
	philo->is_eating = 0;
	philo->is_spleeping = 1;
	philo->have_meal++;
	pthread_mutex_unlock(data->mutex_dead);
	usleep(philo->time_to_eat * 1000);
}

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		msg(gettime() - philo->time_begin, philo->nb, "is sleeping");
	philo->is_spleeping = 0;
	philo->is_thinking = 1;
	pthread_mutex_unlock(data->mutex_dead);
	usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
		msg(gettime() - philo->time_begin, philo->nb, "is thinking");
	philo->is_eating = 1;
	philo->is_thinking = 0;
	pthread_mutex_unlock(data->mutex_dead);
}
