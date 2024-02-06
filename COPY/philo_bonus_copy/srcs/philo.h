/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:37 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/01 22:47:05 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdatomic.h>
// # define PHI 1000
# define TTT 1000
// # define DELTA 20

typedef struct s_args
{
	int	phi;
	int	die;
	int	eat;
	int	sleep;
	int	max_eat;
}	t_args;

typedef struct s_data
{
	int				id;
	sem_t			*forks;
	sem_t			*action;
	sem_t			**end;
	long long		start;
	long long		ate;
	int				meals;
	int				running;
	t_args			*arg;
	pthread_t		routine;
	pthread_t		exitor;
	sem_t			*knife;
	sem_t			*first_dead;
	sem_t			*mutex_run;
	sem_t			*mutex_eat;
	sem_t			*mutex_meals;
	sem_t			*mutex_max;
}	t_data;

void		exit_cleanly(int *pids, t_data *d, int return_value);
void		end_semas_close(t_data *d, int last, int unlink);
void		send_philos(int *pids, t_args args, t_data*d);
int			end_semas_init(t_data *d, t_args args, int i);
void		ft_wait(t_data *d, t_args args, int *pids);
int			ft_parsing(int ac, char **av, t_args *arg);
void		kill_everyone(int *pids, int dead, int n);
int			init_all_semas(t_data *d, t_args args);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_init_data(t_data *d, t_args *args);
void		ft_init_named(t_data *d, t_args args);
int			check_threads(int *pids, t_data *d);
sem_t		*init_sem(char *name, int value);
void		if_dea(t_data *d, int action);
void		ft_putstr_fd(char *s, int fd);
void		unlock_everyone(t_data *d);
void		unlock_everyone(t_data *d);
void		end_semas_unlink(int last);
int			ft_atoi(const char *str);
void		ft_error_named(t_data *d);
void		ft_close_semas(t_data *d);
void		*ft_start_all(void *data);
int			ft_verif_atoi(char *str);
void		philo_process(t_data *d);
void		sleep_think(t_data *d);
void		ft_monitor(t_data *d);
void		*routine(void *data);
int			ft_issign(char c);
int			ft_isdigit(int c);
void		eat(t_data *d);
long long	ft_time(void);
long long	r_ate(t_data *d);
void		w_ate(t_data *d, long long value);
long long	r_meals(t_data *d);
void		w_meals(t_data *d);
int			r_run(t_data *d);
void		w_run(t_data *d);
int			r_max(t_data *d);
void		w_max(t_data *d, int value);
void		ft_error_mutex(t_data *d);
void		ft_init_mutex(t_data *d, t_args args);

#endif