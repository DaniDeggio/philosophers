/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:31:18 by deggio            #+#    #+#             */
/*   Updated: 2023/11/14 23:43:57 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->t_die = ft_atoi(data, av[2]);
	data->t_eat = ft_atoi(data, av[3]);
	data->t_sleep = ft_atoi(data, av[4]);
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
		ft_exit(data, 2);
	if (ac == 6)
		data->n_eat = ft_atoi(data, av[5]);
	else
		data->n_eat = -1;
	if (ac == 6 && data->n_eat < 0)
		ft_exit(data, 2);
	data->start = get_current_time(data);
	if (pthread_mutex_init(&data->lock_death, NULL))
		ft_exit(data, 2);
	data->phi = (t_phi *)malloc(sizeof(t_phi) * data->n_phi);
	if (!data->phi)
		ft_exit(data, 2);
	data->dead = 0;
}

void	init_phi(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phi)
	{
		data->phi[i].id = i + 1;
		data->phi[i].next = (i + 1) % data->n_phi;
		data->phi[i].n_eated = 0;
		data->phi[i].eating = 0;
		data->phi[i].lst_meat = get_current_time(data);
		if (pthread_mutex_init(&data->phi[i].fork, NULL))
			ft_exit(data, 1);
		data->phi[i].data = data;
		i++;
	}
}
