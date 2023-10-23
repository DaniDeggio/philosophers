/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:35 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/23 04:11:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_phi
{
	pthread_t		thread;
	int				id;
	int				n_eated;
	int				nxt;
	pthread_mutex_t	*fork;
	t_data			*data;
}				t_phi;

typedef struct data
{
	int				n_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_death;
	int				n_phi;
	t_phi			*phi;
}				t_data;

//utils
int	ft_atoi(const char *str);
void	ft_exit(int n);