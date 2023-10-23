/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:39 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/23 19:57:22 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_phi *phi)
{
	printf("Sono il thread %d\n", phi->id);
}

void	init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->t_die = ft_atoi(data, av[2]);
	data->t_eat = ft_atoi(data, av[3]);
	data->t_sleep = ft_atoi(data, av[4]);
	if (ac == 6)
		data->n_eat = ft_atoi(data, av[5]);
	else
		data->n_eat = -1;
	data->start = get_current_time(data);
	data->phi = (t_phi *)malloc(sizeof(t_phi) * data->n_phi);
	while (i < data->n_phi)
	{
		data->phi[i].id = i;
		data->phi[i].n_eated = 0;
		data->phi[i].nxt = (i + 1) % data->n_phi; //Questo è geniale non voglio cambiarlo
		pthread_mutex_init(&data->phi[i].fork, NULL); //gestire errori
		data->phi[i].data = data;
		i++;
	}

}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		ft_exit(data, 2);
	data->n_phi = ft_atoi(data, av[1]);
	init(ac, av, data);
	while (i++ < data->n_phi)
		pthread_create(&data->phi[i].thread, NULL, (void *)routine, &data->phi[i]);
	while (i-- < 0)
		pthread_join(data->phi[i].thread, NULL);
	ft_exit(data, -1);
	return (0);
}
