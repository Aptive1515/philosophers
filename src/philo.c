/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:09:32 by aptive            #+#    #+#             */
/*   Updated: 2022/04/03 08:06:38 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_data	**ft_philo_init(t_data *(*data), char **argv, pthread_mutex_t *(*fork))
{
	int	i;
		unsigned long long	time_begin_all;
	int nb_philo;

	nb_philo = ft_atoi(argv[1]);
	i = 0;
	data = malloc(sizeof(data) * nb_philo);
	time_begin_all = gettime();
	while (i < nb_philo)
	{
		data[i] = malloc(sizeof(t_data));
		data[i]->philo = malloc(sizeof(t_philo));
		data[i]->philo->thread_philo_nb = i;
		data[i]->philo->nb = i + 1;
		data[i]->philo->num_fork = 1;
		data[i]->philo->is_eating = 1;
		data[i]->philo->is_thinking = 1;
		data[i]->philo->is_dead = 0;
		gettimeofday(&data[i]->philo->s_time_last, NULL);
		data[i]->fork_r = fork[i];

		data[i]->philo->time_to_die = ft_atoi(argv[2]);
		data[i]->philo->time_to_eat = ft_atoi(argv[3]);
		data[i]->philo->time_to_sleep = ft_atoi(argv[4]);

		if (argv[5])
			data[i]->philo->number_of_times_each_philosopher_must_eat =  ft_atoi(argv[5]);
		else
			data[i]->philo->number_of_times_each_philosopher_must_eat = 0;
		data[i]->philo->time_begin = time_begin_all;
//		printf("%d\n", i + 1);
		if (i + 1 == nb_philo)
			data[i]->fork_l = fork[0];
		else
			data[i]->fork_l = fork[i + 1];
		i++;
	}
	data[i] = NULL;
	return (data);
}

int ft_philo_dead(t_data *(*data))
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i]->philo->is_dead == 1)
			return (0);
		i++;
	}
	return (1);
}
