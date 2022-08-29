/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/08/29 15:23:31 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_data	*data;
	int		k;

	data = arg;
	k = 1;
	pthread_mutex_lock(data->to_print);
	pthread_mutex_unlock(data->to_print);
	while (k)
	{
		if (data->philo->is_eating)
			eating_odd_even(data);
		else if (data->philo->is_spleeping)
			sleeping(data->philo, data);
		else if (data->philo->is_thinking)
			thinking(data->philo, data);
		pthread_mutex_lock(data->mutex_dead);
		k = witch_k(data);
		pthread_mutex_unlock(data->mutex_dead);
	}
	return (arg);
}

int	witch_k(t_data *data)
{
	if (data->dead_philo)
		return (0);
	else if (data->philo->nb_philo_must_eat == -1)
		return (1);
	else if (data->philo->have_meal >= data->philo->nb_philo_must_eat)
		return (0);
	return (1);
}

void	drop_fork(t_data *data)
{
	if (data->philo->nb % 2)
	{
		pthread_mutex_unlock(data->fork_r);
		pthread_mutex_unlock(data->fork_l);
	}
	else
	{
		pthread_mutex_unlock(data->fork_l);
		pthread_mutex_unlock(data->fork_r);
	}
}

void	taking_fork(t_data *data)
{
	if (data->philo->nb % 2)
	{
		pthread_mutex_lock(data->fork_r);
		take_fork(data->philo, data);
		pthread_mutex_lock(data->fork_l);
		take_fork(data->philo, data);
	}
	else
	{
		pthread_mutex_lock(data->fork_l);
		take_fork(data->philo, data);
		pthread_mutex_lock(data->fork_r);
		take_fork(data->philo, data);
	}
}

void	eating_odd_even(t_data *data)
{
	if (data->philo->nb_philo == 1)
		return ;
	taking_fork(data);
	eating(data->philo, data);
	drop_fork(data);
}
