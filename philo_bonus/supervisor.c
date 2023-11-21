/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:26:51 by deggio            #+#    #+#             */
/*   Updated: 2023/11/21 15:47:56 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_eat(t_phi *phi)
{
	sem_wait(phi->data->check);
	if (phi->data->n_eat != -1 && phi->n_eated >= phi->data->n_eat)
	{
		sem_post(phi->data->check);
		sem_wait(phi->data->lock);
		phi->dead = -1;
		sem_post(phi->data->lock);
		return (1);
	}
	sem_post(phi->data->check);
	return (0);
}

int	check_death(t_phi *phi)
{
	sem_wait(phi->data->check);
	if (get_current_time(phi->data) - phi->lst_meat > phi->data->t_die
		&& phi->eating == 0)
	{
		sem_post(phi->data->check);
		print_msg(phi, "died");
		sem_wait(phi->data->lock);
		phi->dead = 1;
		exit(3);
	}
	sem_post(phi->data->check);
	return (0);
}

void	*supervisor(void *philo)
{
	t_phi	*phi;

	phi = (t_phi *)philo;
	while (1)
	{
		if (check_death(phi) == 1 || check_eat(phi) == 1)
			break ;
	}
	return (NULL);
}
