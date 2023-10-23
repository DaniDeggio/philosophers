/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:35 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/23 19:55:11 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


struct	s_data;

typedef struct s_phi
{
	pthread_t				thread;
	int						id;
	int						n_eated;
	int						nxt;
	pthread_mutex_t			fork;
	struct s_data			*data;
}				t_phi;

typedef struct s_data
{
	int				n_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_death;
	int				n_phi;
	size_t			start;
	t_phi			*phi;
}				t_data;

void	routine(t_phi *phi);
void	init(int ac, char **av, t_data *data);

//utils
void	ft_exit(t_data *data, int n);
int		ft_atoi(t_data *data, char *str);
size_t	get_current_time(t_data *data);
int		ft_usleep(t_data *data, size_t ms);
void	print_msg(t_phi *phi, char *str);

#endif