/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:10:26 by tdelauna          #+#    #+#             */
/*   Updated: 2022/08/29 17:19:17 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_all(t_data *(*data))
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data[i]->to_print);
	pthread_mutex_destroy(data[i]->mutex_dead);
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

void	ft_exit(t_data *(*data), int j)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(data[j]->mutex_dead);
	while (data[++i])
		pthread_join (data[i]->philo->thread_philo_nb, NULL);
	free_all(data);
	exit(1);
}

int	philo_all_eat(t_data *(*dt), int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (dt[i]->philo->have_meal >= dt[i]->philo->nb_philo_must_eat)
			i++;
		else
			return (0);
	}
	return (1);
}

void	philo_dead(t_data *(*dt), int nb_philo, int time_to_dead)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	int time;
	usleep((time_to_dead) * 1000);
	while (dt[i])
	{
		time = gettime();
		pthread_mutex_lock(dt[i]->mutex_dead);
		if ((time - dt[i]->philo->last_meal) > dt[i]->philo->time_to_die)
		{
			if (dt[i]->philo->nb_philo_must_eat > 0)
				if (philo_all_eat(dt, nb_philo))
					ft_exit(dt, i);
			printf("%i %i died\n", time - dt[i]->philo->time_begin,
				dt[i]->philo->nb);
			while (dt[++j])
				dt[j]->dead_philo = 1;
			ft_exit(dt, i);
		}
		pthread_mutex_unlock(dt[i]->mutex_dead);
		i++;
		if (nb_philo == i)
		{
			usleep(100);
			i = 0;
		}
	}
}
