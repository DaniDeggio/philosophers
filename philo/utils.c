/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:08:46 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/23 04:40:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data *data,int n)
{
	int i;

	i = 0;
	if (n == 1)
		write(1, "Error\n", 7);
	while (i++ < data->n_phi)
	{
		pthread_mutex_destroy(&data->phi[i].fork);
		free(data->phi);
	}
	free(data);
	if (n != -1)
		exit;
}
int	ft_atoi(const char *str)
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
	if (num > 2147483647 || num < -2147483648 || str[i] != '\0')
		ft_exit(1);
	return (num * sng);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_exit(1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	current;

	current = get_current_time();
	while ((get_current_time() - current) < ms)
		usleep(500);
	return (0);
}