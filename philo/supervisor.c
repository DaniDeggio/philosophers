/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:26:51 by deggio            #+#    #+#             */
/*   Updated: 2023/11/15 06:34:13 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < data->n_phi)
	{
		if (data->n_eat != -1 && data->phi[i].n_eated >= data->n_eat)
			n++;
		i++;
	}
	if (n == data->n_phi)
	{
		pthread_mutex_lock(&data->lock_death);
		data->dead = -1;
		pthread_mutex_unlock(&data->lock_death);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phi)
	{
		if (get_current_time(data) - data->phi[i].lst_meat > data->t_die
			&& data->phi[i].eating == 0)
		{
			print_msg(&data->phi[i], "died");
			pthread_mutex_lock(&data->lock_death);
			data->dead = 1;
			pthread_mutex_unlock(&data->lock_death);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*supervisor(void *dataa)
{
	t_data	*data;

	data = (t_data *)dataa;
	while (1)
	{
		if (check_death(data) == 1 || check_eat(data) == 1)
			break ;
	}
	return (NULL);
}
