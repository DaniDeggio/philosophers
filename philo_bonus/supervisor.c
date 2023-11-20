/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:26:51 by deggio            #+#    #+#             */
/*   Updated: 2023/11/20 02:40:28 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_eat(t_phi phi)
{
	if (phi.data->n_eat != -1 && phi.n_eated >= phi.data->n_eat)
		phi.data->eated++;
	if (phi.data->eated == phi.data->n_phi)
	{
		sem_wait(phi.data->lock);
		phi.dead = -1;
		return (1);
	}
	return (0);
}

int	check_death(t_phi phi)
{
	if (get_current_time(phi.data) - phi.lst_meat > phi.data->t_die
		&& phi.eating == 0)
	{
		print_msg(phi, "died");
		sem_wait(phi.data->lock);
		phi.dead = -1;
		exit(3);
	}
	return (0);
}

void	*supervisor(void *philo)
{
	t_phi	*phi;

	phi = (t_phi *)philo;
	phi->lst_meat = get_current_time(phi->data);
	while (1)
	{
		if (check_death(*phi) == 1 || check_eat(*phi) == 1)
			break ;
	}
	return (NULL);
}
