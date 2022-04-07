/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/04/07 16:21:10 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), char **argv)
{
	int		i;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	data = malloc(sizeof(data) * (nb_philo + 1));
	i = 0;
	while (i < nb_philo)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		data[i]->philo->nb = 1 + i;
		data[i]->philo->num_fork = 1;
		data[i]->dead_philo = 0;
		if ((i + 1) % 2 == 0)
		{
			data[i]->philo->is_eating = 1;
			data[i]->philo->is_thinking = 0;
		}
		else
		{
			data[i]->philo->is_eating = 0;
			data[i]->philo->is_thinking = 1;
		}
		data[i]->philo->is_dead = 0;
		data[i]->fork_r = (pthread_mutex_t *)malloc(sizeof(*(data[i]->fork_r)));
		pthread_mutex_init(data[i]->fork_r, NULL);
		data[i]->philo->time_to_die = ft_atoi(argv[2]);
		data[i]->philo->time_to_eat = ft_atoi(argv[3]);
		data[i]->philo->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data[i]->philo->number_philosopher_must_eat = ft_atoi(argv[5]);
		else
			data[i]->philo->number_philosopher_must_eat = 0;
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		if (i + 1 == nb_philo)
			data[i]->fork_l = data[0]->fork_r;
		else
			data[i]->fork_l = data[i + 1]->fork_r;
		i++;
	}
	return (data);
}

int	ft_philo_dead(t_data *(*data))
{
	int	i;
	int	j;

	i = 0;
	while (data[i])
	{
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

void	ft_init_mutex(t_data *(*data))
{
	pthread_mutex_t	*to_print;
	pthread_mutex_t	*mutex_dead;
	int				i;

	i = 0;
	to_print = (pthread_mutex_t *)malloc(sizeof(*(to_print)));
	mutex_dead = (pthread_mutex_t *)malloc(sizeof(*(mutex_dead)));
	pthread_mutex_init(to_print, NULL);
	pthread_mutex_init(mutex_dead, NULL);
	while (data[i])
	{
		data[i]->to_print = to_print;
		data[i]->mutex_dead = mutex_dead;
		data[i]->dead_philo = 0;
		i++;
	}
}
