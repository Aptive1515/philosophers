/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/08/10 20:19:09 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*(*data);
	int		i;

	if (argc < 5 || argc > 6 || ft_atoi(argv[5]) <= 0)
		return (1);
	i = 0;
	data = NULL;
	data = philo_init(data, argv);
	init_mutex(data);
	i = -1;
	pthread_mutex_lock(data[0]->to_print);
	while (data[++i])
		pthread_create(&data[i]->philo->thread_philo_nb,
			NULL, routine, data[i]);
	pthread_mutex_unlock(data[0]->to_print);
	philo_dead(data, ft_atoi(argv[1]), ft_atoi(argv[2]));
	return (1);
}
