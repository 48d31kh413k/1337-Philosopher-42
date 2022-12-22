#include <philo.h>

static void	philo_mange(t_philo *philo)
{
	t_table	*tab;

	tab = philo->tab;
	pthread_mutex_lock(&philo->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	if (philo->tab->nombre_de_philos == 1)
	{
		passe_temps(tab, tab->temps_de_famine);
		afficher_message(philo, MESSAGE_MORT);
		pthread_mutex_unlock(&philo->fourchette);
		tab->mort = 1;
		return ;
	}
	pthread_mutex_lock(&philo->suivant->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	pthread_mutex_lock(&tab->verifier);
	philo->nombre_manger++;
	afficher_message(philo, MESSAGE_MANGER);
	philo->dernier_repas = temps_actuel();
	pthread_mutex_unlock(&tab->verifier);
	passe_temps(tab, tab->temps_de_manger);
	pthread_mutex_unlock(&philo->fourchette);
	pthread_mutex_unlock(&philo->suivant->fourchette);
}

void	*la_vie(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	if (philo->identifiant % 2 == 0)
		usleep(1000);
	while (!tab->mort && !tab->satiete)
	{
		philo_mange(philo);
		afficher_message(philo, MESSAGE_SOMMEIL);
		passe_temps(tab, tab->temps_de_sommeil);
		afficher_message(philo, MESSAGE_PENSER);
	}
	return (NULL);
}
