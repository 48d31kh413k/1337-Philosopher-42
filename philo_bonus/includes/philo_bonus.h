#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>


enum e_msg {
	MESSAGE_FOURCHETTE = 0,
	MESSAGE_MANGER,
	MESSAGE_SOMMEIL,
	MESSAGE_PENSER,
	MESSAGE_MORT
};

typedef struct s_philo
{
	int				identifiant;
	int				nombre_manger;
	size_t			dernier_repas;
	struct s_philo	*suivant;
	struct s_philo	*precedent;
	struct s_table	*tab;
	pid_t			pid;
	pthread_t		verifier_dead;
}	t_philo;


typedef struct s_table
{
	int				temps_de_famine;
	int				temps_de_manger;
	int				temps_de_sommeil;
	int				nombre_de_repas;
	int				nombre_de_philos;
	int				satiete;
	int				mort;
	size_t			t_0;
	t_philo			*philos;
	sem_t			*afficher;
	sem_t			*verifier;
	sem_t			*fourchette;
}	t_table;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		verifier_args(int argc, char *argv[], t_table *tab);
void	afficher_message(t_philo *philo, int message);
void	*la_vie(void *arg);
void	la_sortie(t_table *tab);
size_t	temps_actuel(void);
void	passe_temps(t_table *tab, size_t temps);
void	*verifier_la_mort(void *arg);

#endif
