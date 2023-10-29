/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:39 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/29 20:43:36 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(t_phi *phi)
{
	while (phi->data->dead == 0)
	{
		if (phi->data->n_eat != -1 && phi->n_eated >= phi->data->n_eat)
		{
			phi->data->dead = -1;
			break ;
		}
		if (get_current_time(phi->data) - phi->lst_meat > phi->data->t_die && phi->eating == 0)
		{
			print_msg(phi, "died");
			phi->data->dead = 1;
			break ;
		}
	}
	// printf("phi->data->dead = %i\n", phi->data->dead);
	return (NULL);
}

void	*routine(t_phi *phi)
{
	if (phi->id % 2 != 0)
		ft_usleep(phi->data, 10);
	pthread_create(&phi->supervisor, NULL, (void *)supervisor, phi);
	pthread_detach(phi->supervisor);
	while (phi->data->dead == 0)
	{
		pthread_mutex_lock(&phi->fork);
		print_msg(phi, "has taken a fork");
		pthread_mutex_lock(&phi->data->phi[phi->nxt].fork);
		print_msg(phi, "has taken a fork");
		pthread_mutex_lock(&phi->data->lock);
		phi->eating = 1;
		phi->lst_meat = get_current_time(phi->data);
		print_msg(phi, "is eating");
		pthread_mutex_unlock(&phi->data->lock);
		ft_usleep(phi->data, phi->data->t_eat);
		// printf("Finito de magna\n");
		pthread_mutex_unlock(&phi->fork);
		pthread_mutex_unlock(&phi->data->phi[phi->nxt].fork);
		phi->n_eated++;
		phi->eating = 0;
		pthread_mutex_lock(&phi->data->lock);
		print_msg(phi, "is sleeping");
		ft_usleep(phi->data, phi->data->t_sleep);
		pthread_mutex_unlock(&phi->data->lock);
		print_msg(phi, "is thinking");
	}
	printf(" DIOCANE  phi->data->dead = %i\n", phi->data->dead);
	pthread_join(phi->supervisor, NULL);
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
	data->dead = 0;
	data->start = get_current_time(data);
	data->phi = (t_phi *)malloc(sizeof(t_phi) * data->n_phi);
	pthread_mutex_init(&data->lock, NULL);
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

	i = -1;
	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		ft_exit(data, 2);
	data->n_phi = ft_atoi(data, av[1]);
	//printf("inizio init \n");
	init(ac, av, data);
	//printf(" creazione trhead   \n");
	while (++i < data->n_phi)
		pthread_create(&data->phi[i].thread, NULL, (void *)routine, &data->phi[i]);
	printf("join   \n");
	i = -1;
	while (++i < data->n_phi)
		pthread_join(data->phi[i].thread, NULL);
	printf(" exit \n");
	ft_exit(data, -1);
	return (0);
}
