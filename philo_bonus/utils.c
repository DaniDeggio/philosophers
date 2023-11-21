/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:08:46 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/21 15:52:27 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_data *data, int n)
{
	if (n == 1 || n == 2 || n == 3)
		write(1, "Error\n", 7);
	if (n != 1)
		free(data);
	if (n != 1 && n != 2)
	{
		sem_close(data->forks);
		sem_close(data->lock);
		sem_close(data->check);
		sem_unlink("forks");
		sem_unlink("lock");
		sem_unlink("check");
	}
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
		ft_exit(data, 3);
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
	if (!death(phi))
	{
		sem_wait(phi->data->lock);
		printf("%zu %d %s\n", get_current_time(phi->data) - phi->data->start,
			phi->id, str);
		sem_post(phi->data->lock);
	}
}
