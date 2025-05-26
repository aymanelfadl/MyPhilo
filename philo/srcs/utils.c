#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	print_philo_state(t_philo *philo, int state)
{
	printf("%lld ", get_time() - philo->table->start_time);
	printf("%d ", philo->id);
	if (state == THINKING)
		printf("is thinking\n");
	else if (state == EATING)
		printf("is eating\n");
	else if (state == SLEEPING)
		printf("is sleeping\n");
	else if (state == TOOK_FORK)
		printf("has taken a fork\n");
	else if (state == DIED)
		printf("died\n");
}

void	print_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	pthread_mutex_lock(&philo->table->death_mutex);
	
	if (philo->table->someone_died == 0 || state == DIED)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		print_philo_state(philo, state);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	smart_sleep(long long time_to_wait)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time_to_wait)
		usleep(100);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}
