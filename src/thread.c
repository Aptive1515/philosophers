/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:02:51 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 15:38:14 by aptive           ###   ########.fr       */
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
	// int		k;

	// k = 0;
	data = arg;
	pthread_mutex_lock(data->to_print);
	pthread_mutex_unlock(data->to_print);
	data->philo->time_begin = gettime();
	data->philo->last_meal = data->philo->time_begin;
	while (1)
	{
		if (data->philo->is_eating)
		{
			if (data->philo->nb % 2)
			{
				pthread_mutex_lock(data->fork_l);
				pthread_mutex_lock(data->fork_r);
				ft_take_fork(data->philo, data);
				ft_eating(data->philo, data);
				pthread_mutex_unlock(data->fork_l);
				pthread_mutex_unlock(data->fork_r);
			}
			else
			{
				pthread_mutex_lock(data->fork_r);
				pthread_mutex_lock(data->fork_l);
				ft_take_fork(data->philo, data);
				ft_eating(data->philo, data);
				pthread_mutex_unlock(data->fork_l);
				pthread_mutex_unlock(data->fork_r);
			}
		}
		if (data->philo->is_spleeping)
			ft_sleeping(data->philo, data);
		if (data->philo->is_thinking)
			ft_thinking(data->philo, data);
	}
	return (arg);
}

void	ft_take_fork(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		ft_msg(gettime() - philo->time_begin , philo->nb, "has taken a fork");
		ft_msg(gettime() - philo->time_begin , philo->nb, "has taken a fork");
	}
	pthread_mutex_unlock(data->mutex_dead);
}

void	ft_eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->mutex_dead);
	if (!data->dead_philo)
	{
		ft_msg(gettime() - philo->time_begin , philo->nb, "is eating");
	}
		philo->last_meal = gettime();
		pthread_mutex_unlock(data->mutex_dead);
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
