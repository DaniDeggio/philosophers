/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:24:33 by deggio            #+#    #+#             */
/*   Updated: 2023/11/14 23:51:15 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if	(n == data->n_phi)
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
		if (get_current_time(data) - data->phi[i].lst_meat > data->t_die && data->phi[i].eating == 0)
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
	//usleep(phi->data->t_eat / 10);
	//print_msg(phi, "dopo usleep");
	pthread_mutex_unlock(&phi->fork);
	pthread_mutex_unlock(&phi->data->phi[phi->next].fork);
	phi->eating = 0;
	phi->n_eated++;
}

void	sleep_think(t_phi *phi)
{
	print_msg(phi, "is sleeping");
	ft_usleep(phi->data, phi->data->t_sleep);
	//usleep(phi->data->t_sleep / 10);
	print_msg(phi, "is thinking");
}

void *routine(void *philo)
{
	t_phi	*phi;

	phi = (t_phi *)philo;
	if (phi->id % 2 == 0)
		ft_usleep(phi->data, 1);
	// if (phi->id % 2 != 0)
	// 	usleep(10);
	//while (phi->data->dead == 0)
	while (life(phi->data))
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
	return (NULL);
}

void	start(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->supervisor, NULL, &supervisor, data))
		ft_exit(data, 1);
	while (i < data->n_phi)
	{
		if (pthread_create(&data->phi[i].thread, NULL, &routine, (void *)&data->phi[i]))
			ft_exit(data, 1);
		//pthread_detach(data->phi[i].thread);
		i++;
	}
	pthread_join(data->supervisor, NULL);
	i = 0;
	while (i < data->n_phi)
	{
		pthread_join(data->phi[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		ft_exit(data, 2);
	data->n_phi = ft_atoi(data, av[1]);
	if (data->n_phi > 200)
		ft_exit(data, 2);
	init_data(ac, av, data);
	init_phi(data);
	start(data);
	ft_exit(data, -1);
	return (0);
}
