/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:28:31 by deggio            #+#    #+#             */
/*   Updated: 2023/11/21 15:48:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	death(t_phi *phi)
{
	sem_wait(phi->data->lock);
	if (phi->dead == 1)
	{
		sem_post(phi->data->lock);
		return (1);
	}
	sem_post(phi->data->lock);
	return (0);
}

void	eat(t_phi *phi)
{
	sem_wait(phi->data->forks);
	print_msg(phi, "has taken a fork");
	sem_wait(phi->data->forks);
	print_msg(phi, "has taken a fork");
	sem_wait(phi->data->check);
	phi->eating = 1;
	phi->lst_meat = get_current_time(phi->data);
	phi->n_eated++;
	sem_post(phi->data->check);
	print_msg(phi, "is eating");
	ft_usleep(phi->data, phi->data->t_eat);
	sem_post(phi->data->forks);
	sem_post(phi->data->forks);
	sem_wait(phi->data->check);
	phi->eating = 0;
	sem_post(phi->data->check);
}

void	sleep_think(t_phi *phi)
{
	print_msg(phi, "is sleeping");
	ft_usleep(phi->data, phi->data->t_sleep);
	print_msg(phi, "is thinking");
}

void	routine(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		data->phi.id = i + 1;
		data->phi.lst_meat = get_current_time(data);
		if (data->phi.id % 2 == 0)
			ft_usleep(data, 10);
		if (pthread_create(&data->phi.supervisor, NULL,
				supervisor, (void *)&data->phi))
			ft_exit(data, 3);
		pthread_detach(data->phi.supervisor);
		while (!death(&data->phi))
		{
			eat(&data->phi);
			sleep_think(&data->phi);
		}
	}
	else
		data->pid[i] = pid;
}
