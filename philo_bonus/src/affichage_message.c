#include <philo_bonus.h>

static char	*obtenir_message(int message)
{
	if (message == MESSAGE_FOURCHETTE)
		return (" has taken a fork");
	if (message == MESSAGE_MANGER)
		return (" is eating");
	if (message == MESSAGE_SOMMEIL)
		return (" is sleeping");
	if (message == MESSAGE_PENSER)
		return (" is thinking");
	if (message == MESSAGE_MORT)
		return (" died");
	return ("Error: not valid msg id");
}

void	afficher_message(t_philo *philo, int message)
{
	size_t	t;

	t = temps_actuel() - philo->tab->t_0;
	sem_wait(philo->tab->afficher);
	if (!philo->tab->mort && !philo->tab->satiete)
	{
		printf("%6ld", t);
		printf(" %3d ", philo->identifiant);
		printf("%s", obtenir_message(message));
		printf("\n");
	}
	sem_post(philo->tab->afficher);
}
