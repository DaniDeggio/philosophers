/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:39 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/28 18:44:58 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* supervisor(t_phi *sv)
{
	int	i;

	while (sv->data->dead == 0)
	{
		i = 0;
		while (i < sv->data->n_phi)
		{
			if (sv->data->n_eat != -1 && sv->data->phi[i].n_eated >= sv->data->n_eat)
			{
				sv->data->dead = -1;
				return NULL;
			}
			if (get_current_time(sv->data) - sv->data->phi[i].lst_meat > sv->data->t_die)
			{
				print_msg(&sv->data->phi[i], "died\n");
				sv->data->dead = 1;
				return NULL;
			}
			i++;
		}
	}
	return NULL;
}
void* routine(t_phi *phi)
{
	while (phi->data->dead == 0)
	{
		pthread_mutex_lock(&phi->fork);
		print_msg(phi, "has taken a fork\n");
		pthread_mutex_lock(&phi->data->phi[phi->nxt].fork);
		print_msg(phi, "has taken a fork\n");
		phi->eating = 1;
		phi->lst_meat = get_current_time(phi->data);
		print_msg(phi, "is eating\n");
		ft_usleep(phi->data, phi->data->t_eat);
		pthread_mutex_unlock(&phi->fork);
		pthread_mutex_unlock(&phi->data->phi[phi->nxt].fork);
		phi->n_eated++;
		phi->eating = 0;
		print_msg(phi, "is sleeping\n");
		ft_usleep(phi->data, phi->data->t_sleep);
		print_msg(phi, "is thinking\n");
	}
	return NULL;
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
	data->supervisor.data = data;
	while (i < data->n_phi)
	{
		//printf("       Creo filosofo   i = %i  \n", i);
		data->phi[i].id = i;
		data->phi[i].n_eated = 0;
		data->phi[i].nxt = (i + 1) % data->n_phi; //Questo è geniale non voglio cambiarlo
		pthread_mutex_init(&data->phi[i].fork, NULL); //gestire errori
		data->phi[i].data = data;
		data->phi[i].eating = 0;
		data->phi[i].lst_meat = get_current_time(data);
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
	//printf("inizio init \n");
	init(ac, av, data);
	//printf(" creazione trhead   \n");
	while (i++ < data->n_phi)
		pthread_create(&data->phi[i].thread, NULL, (void *)routine, &data->phi[i]);
	pthread_create(&data->supervisor.thread, NULL, (void *)supervisor, &data->supervisor);
	//printf("join   \n");
	while (i-- < 0)
		pthread_join(data->phi[i].thread, NULL);
	//printf(" exit \n");
	ft_exit(data, -1);
	return (0);
}
