/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aptive <aptive@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:29 by aptive            #+#    #+#             */
/*   Updated: 2022/04/03 09:11:18 by aptive           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//int pthread_create (pthread_t *thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);

void *ft_test2(char	*nb)
{
	printf("fct thread 2 \n");
	printf("fct thread : %s\n", nb);

	return(nb);
}

int	main(int argc, char **argv)
{
	/*unsigned long long	time_begin;

	(void)argc;
	(void)argv;

	time_begin = gettime();
	printf("time begin %lld\n",time_begin);
	usleep(1000);
	printf("%lld\ntime end %lld\n",gettime(),(gettime() - time_begin) * 100);
	usleep(2000);
	printf("%lld\ntime end %lld\n",gettime(),(gettime() - time_begin) * 100);
*/
	t_data	*(*data);
	static pthread_mutex_t	*(*fork);
	int		i;
	int number_of_philosophers;



	number_of_philosophers = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		return (1);



	(void)fork;
	(void)argc;
	(void)argv;

	fork = malloc(sizeof(fork) * number_of_philosophers);
	if(!fork)
		return (0);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		fork[i] = malloc(sizeof(fork));
		//printf("fork %d %p\n", i + 1, fork[i]);
		i++;
	}
	data = NULL;
	data = ft_philo_init(data, argv, fork);
	/*i = -1;
	while (data[++i])
	{




		printf("philo : %d, fork right %p, fork left %p\n", data[i]->philo->nb, data[i]->fork_r, data[i]->fork_l);

	}
	printf("HERE\n");
*/


	i = -1;
	while (data[++i])
	{
		pthread_create (&data[i]->philo->thread_philo_nb, NULL, ft_test, data[i]);
		//pthread_join (tab_philo[i]->thread_philo_nb, NULL);
	}

	while(ft_philo_dead(data))
	{}
	return (1);
}
