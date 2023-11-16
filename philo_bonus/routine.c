/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:28:31 by deggio            #+#    #+#             */
/*   Updated: 2023/11/16 05:15:59 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_phi phi)
{
	sem_wait(phi.data->forks);
	print_msg(phi, "has taken a fork");
	sem_wait(phi.data->forks);
	print_msg(phi, "has taken a fork");
	phi.eating = 1;
	phi.lst_meat = get_current_time(phi.data);
	print_msg(phi, "is eating");
	ft_usleep(phi.data, phi.data->t_eat);
	sem_post(phi.data->forks);
	sem_post(phi.data->forks);
	phi.eating = 0;
	phi.n_eated++;
}

void	sleep_think(t_phi phi)
{
	print_msg(phi, "is sleeping");
	ft_usleep(phi.data, phi.data->t_sleep);
	print_msg(phi, "is thinking");
}

void	routine(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		data->phi.id = i + 1;
		if (data->phi.id % 2 == 0)
			ft_usleep(data, 10);
		if (pthread_create(&data->phi.supervisor, NULL,
				supervisor, (void *)&data->phi))
			ft_exit(data, 3);
		pthread_detach(data->phi.supervisor);
		while (!data->phi.dead)
		{
			eat(data->phi);
			sleep_think(data->phi);
		}
		sem_close(data->forks);
	}
	else
		data->pid[i] = pid;
}
