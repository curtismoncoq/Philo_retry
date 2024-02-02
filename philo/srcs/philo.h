/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:37 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/24 19:21:55 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# define PHI 1000
# define TTT 1000
# define DELTA 20

typedef struct s_args
{
	int	phi;
	int	die;
	int	eat;
	int	sleep;
	int	max_eat;
}	t_args;

typedef struct s_time
{
	long long		start;
	int				start_lock;
	int				ended;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	start_mutex;
}	t_time;

typedef struct s_both
{
	t_args	args;
	t_time	t;
}	t_both;

typedef struct s_data
{
	int				id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_next;
	pthread_mutex_t	*ate_mutex;
	pthread_mutex_t	*end_mutex;
	pthread_mutex_t	*start_mutex;
	long long		*start;
	long long		ate;
	int				*ended;
	int				*start_lock;
	int				meals;
	t_args			*arg;
}	t_data;

int			ft_alloc(pthread_t **threads,
				pthread_mutex_t **mutex, t_data **d, int phi);
void		ft_join(pthread_t *thread, t_data *d,
				t_time *t, pthread_t *monitor);
void		ft_free_alloc(pthread_t *threads,
				pthread_mutex_t *mutex, t_data *d);
int			ft_init_mutex(t_data *d, pthread_mutex_t *mutex, pthread_t *thread);
int			ft_init_threads(t_data *d, pthread_t *monitor, pthread_t *thread);
int			ft_fail(pthread_t *thread, t_data *d, int th, int mut);
int			ft_init_data(t_data *d, t_time *t, t_args *args);
void		ft_while_monitor(t_data *d, int i, int finito);
int			ft_parsing(int ac, char **av, t_args *arg);
void		*ft_calloc(size_t nmemb, size_t size);
void		w_ate(t_data *d, long long value);
void		w_ended(t_data *d, int value);
void		w_start(t_data *d, int value);
void		ft_putstr_fd(char *s, int fd);
void		*ft_start_all(void *data);
int			ft_atoi(const char *str);
int			ft_verif_atoi(char *str);
void		*ft_monitor(void *data);
void		take_forks_2(t_data *d);
void		take_forks_1(t_data *d);
void		sleep_think(t_data *d);
void		*routine2(void *data);
void		*routine(void *data);
long long	r_meals(t_data *d);
void		w_meals(t_data *d);
int			r_ended(t_data *d);
int			r_start(t_data *d);
int			ft_issign(char c);
int			ft_isdigit(int c);
long long	r_ate(t_data *d);
void		eat(t_data *d);
long long	ft_time(void);

#endif