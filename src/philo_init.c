/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelauna <tdelauna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/08/09 14:43:02 by tdelauna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), char **argv)
{
	int		i;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	data = malloc(sizeof(data) * (nb_philo + 1));
	if (!data)
		return (NULL);
	data[nb_philo] = NULL;
	i = 0;
	while (i < nb_philo)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		data[i]->fork_r = (pthread_mutex_t *)malloc(sizeof(*(data[i]->fork_r)));
		pthread_mutex_init(data[i]->fork_r, NULL);
		ft_param_to_philo(data[i]->philo, i);
		ft_argv_to_philo(data[i]->philo, argv);
		i++;
	}
	ft_fork_to_philo(data, nb_philo);
	return (data);
}

void	ft_param_to_philo(t_philo *philo, int i)
{
	philo->nb = 1 + i;
	philo->num_fork = 1;
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

void	ft_argv_to_philo(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo->number_philosopher_must_eat = -1;
}

void	ft_fork_to_philo(t_data *(*data), int nb_philo)
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
	while (data && data[i])
	{
		data[i]->to_print = to_print;
		data[i]->mutex_dead = mutex_dead;
		data[i]->dead_philo = 0;
		i++;
	}
}
