/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 19:03:34 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**philo_init(t_data *(*data), char **argv)
{
	int		i;
	int		nb_philo;

	i = 0;
	nb_philo = ft_atoi(argv[1]);
	data = ft_calloc(sizeof(t_data), nb_philo + 1);
	if (!data)
		return (NULL);
	data[nb_philo] = NULL;
	while (i < nb_philo)
	{
		data[i] = ft_calloc(sizeof(t_data), 1);
		data[i]->philo = ft_calloc(sizeof(t_philo), 1);
		data[i]->fork_r = (pthread_mutex_t *)malloc(sizeof(*(data[i]->fork_r)));
		pthread_mutex_init(data[i]->fork_r, NULL);
		param_to_philo(data[i]->philo, i);
		argv_to_philo(data[i]->philo, argv);
		i++;
	}
	fork_to_philo(data, nb_philo);
	return (data);
}

void	param_to_philo(t_philo *philo, int i)
{
	philo->nb = 1 + i;
	philo->num_fork = 1;
	philo->have_meal = 0;
	if ((i + 1) % 2 == 0)
	{
		philo->is_eating = 1;
		philo->is_thinking = 0;
	}
	else
	{
		philo->is_eating = 0;
		philo->is_thinking = 1;
	}
	philo->is_dead = 0;
}

void	argv_to_philo(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nb_philo_must_eat = ft_atoi(argv[5]);
	else
		philo->nb_philo_must_eat = -1;
}

void	fork_to_philo(t_data *(*data), int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (i + 1 == nb_philo)
			data[i]->fork_l = data[0]->fork_r;
		else
			data[i]->fork_l = data[i + 1]->fork_r;
		i++;
	}
}

void	init_mutex(t_data *(*data))
{
	pthread_mutex_t	*to_print;
	pthread_mutex_t	*mutex_dead;
	int				i;

	i = 0;
	to_print = (pthread_mutex_t *)malloc(sizeof(*(to_print)));
	mutex_dead = (pthread_mutex_t *)malloc(sizeof(*(mutex_dead)));
	pthread_mutex_init(to_print, NULL);
	pthread_mutex_init(mutex_dead, NULL);
	while (data && data[i])
	{
		data[i]->to_print = to_print;
		data[i]->mutex_dead = mutex_dead;
		data[i]->dead_philo = 0;
		i++;
	}
}
