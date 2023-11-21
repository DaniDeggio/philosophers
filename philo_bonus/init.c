/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:31:18 by deggio            #+#    #+#             */
/*   Updated: 2023/11/21 15:50:20 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(int ac, char **av, t_data *data)
{
	sem_unlink("forks");
	sem_unlink("lock");
	sem_unlink("check");
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
	data->forks = sem_open("forks", O_CREAT, 0666, data->n_phi);
	data->lock = sem_open("lock", O_CREAT, 0666, 1);
	data->check = sem_open("check", O_CREAT, 0666, 1);
	data->start = get_current_time(data);
}

void	init_phi(t_data *data)
{
	data->phi.id = 0;
	data->phi.n_eated = 0;
	data->phi.eating = 0;
	data->phi.dead = 0;
	data->phi.data = data;
}
