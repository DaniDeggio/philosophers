/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:24:33 by deggio            #+#    #+#             */
/*   Updated: 2023/11/15 06:28:52 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->supervisor, NULL, &supervisor, data))
		ft_exit(data, 1);
	while (i < data->n_phi)
	{
		if (pthread_create(&data->phi[i].thread, NULL,
				&routine, (void *)&data->phi[i]))
			ft_exit(data, 1);
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
