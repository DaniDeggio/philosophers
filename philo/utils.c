/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:08:46 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/15 06:44:29 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *data, int n)
{
	if (n == 1 || n == 2)
		write(1, "Error\n", 7);
	while (data->n_phi > 0 && n != 2 && n != 5)
	{
		pthread_mutex_destroy(&data->phi[data->n_phi - 1].fork);
		data->n_phi--;
	}
	if (n != 2)
		pthread_mutex_destroy(&data->lock_death);
	if (n != 2)
		free(data->phi);
	if (n != 3)
		free(data);
	if (n != -1)
		exit(1);
}

int	ft_atoi(t_data *data, char *str)
{
	size_t	i;
	int		sng;
	long	num;

	i = 0;
	sng = 1;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sng = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num > 2147483647 || num < 0 || str[i] != '\0')
		ft_exit(data, 2);
	return ((int)(num * sng));
}

size_t	get_current_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_exit(data, 1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(t_data *data, size_t ms)
{
	size_t	current;

	current = get_current_time(data);
	while ((get_current_time(data) - current) < ms)
		usleep(500);
	return (0);
}

void	print_msg(t_phi *phi, char *str)
{
	if (life(phi->data))
		printf("%zu %d %s\n", get_current_time(phi->data) - phi->data->start,
			phi->id, str);
}
