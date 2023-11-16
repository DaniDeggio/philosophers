/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:28:31 by deggio            #+#    #+#             */
/*   Updated: 2023/11/16 02:47:44 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	life(t_data *data)
{
	pthread_mutex_lock(&data->lock_death);
	if (data->dead != 0)
	{
		pthread_mutex_unlock(&data->lock_death);
		return (0);
	}
	pthread_mutex_unlock(&data->lock_death);
	return (1);
}

void	eat(t_phi *phi)
{
	pthread_mutex_lock(&phi->fork);
	print_msg(phi, "has taken a fork");
	pthread_mutex_lock(&phi->data->phi[phi->next].fork);
	print_msg(phi, "has taken a fork");
	phi->eating = 1;
	phi->lst_meat = get_current_time(phi->data);
	print_msg(phi, "is eating");
	ft_usleep(phi->data, phi->data->t_eat);
	pthread_mutex_unlock(&phi->fork);
	pthread_mutex_unlock(&phi->data->phi[phi->next].fork);
	phi->eating = 0;
	phi->n_eated++;
}

void	sleep_think(t_phi *phi)
{
	print_msg(phi, "is sleeping");
	ft_usleep(phi->data, phi->data->t_sleep);
	print_msg(phi, "is thinking");
}

void	*routine(t_data *data, int	i)
{
	pid_t	pid;

	pid = fork();
	if(!pid)
	{
		data->phi.id = i;
		if (data->phi.id % 2 == 0)
			ft_usleep(data, 10);
		if (pthread_create(&data->phi.supervisor, NULL, supervisor, &data->phi))
			ft_exit(data, 3);
		
		while (!data->dead)
		{
			if (phi->data->n_phi == 1)
			{
				print_msg(phi, "has taken a fork");
				ft_usleep(phi->data, phi->data->t_die);
				print_msg(phi, "died");
				break ;
			}
			else
			{
				eat(phi);
				sleep_think(phi);
			}
		}
	}
	else
		data->pid[i] = pid;
	return (NULL);
}
