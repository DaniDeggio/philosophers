/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:24:33 by deggio            #+#    #+#             */
/*   Updated: 2023/11/21 15:06:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start(t_data *data)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < data->n_phi)
	{
		routine(data, i);
		i++;
	}
	i = 0;
	while (i < data->n_phi)
	{
		waitpid(-1, &status, 0);
		if (WSTOPSIG(status) == 3)
		{
			j = -1;
			while (++j < data->n_phi)
				kill(data->pid[j], SIGKILL);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit(data, 1);
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
