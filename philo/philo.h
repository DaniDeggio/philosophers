/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:59:35 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/15 06:34:18 by deggio           ###   ########.fr       */
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
	int						next;
	int						n_eated;
	int						eating;
	size_t					lst_meat;
	pthread_mutex_t			fork;
	struct s_data			*data;
}				t_phi;

typedef struct s_data
{
	int				n_phi;
	size_t			t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	size_t			start;
	pthread_mutex_t	lock_death;
	t_phi			*phi;
	int				dead;
	pthread_t		supervisor;
}				t_data;

//philo
void	start(t_data *data);

//init
void	init_data(int ac, char **av, t_data *data);
void	init_phi(t_data *data);

//supervisor
int		check_eat(t_data *data);
int		check_death(t_data *data);
void	*supervisor(void *data);

//routine
int		life(t_data *data);
void	eat(t_phi *phi);
void	sleep_think(t_phi *phi);
void	*routine(void *philo);

//utils
void	ft_exit(t_data *data, int n);
int		ft_atoi(t_data *data, char *str);
size_t	get_current_time(t_data *data);
int		ft_usleep(t_data *data, size_t ms);
void	print_msg(t_phi *phi, char *str);

#endif