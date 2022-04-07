/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/04/07 16:08:30 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*(*data);
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	data = NULL;
	data = ft_philo_init(data, argv);
	ft_init_mutex(data);
	i = -1;
	while (data[++i])
	{
		pthread_create(&data[i]->philo->thread_philo_nb,
			NULL, ft_test, data[i]);
	}
	while (ft_philo_dead(data))
		i = -1;
	while (data[++i])
		pthread_join (data[i]->philo->thread_philo_nb, NULL);
	return (1);
}
