philo_init.c
Contient les fonctions d'initialisation des philosophes:

init_philosophers: Crée tous les philosophes
init_philo_vars: Initialise les variables d'un philosophe
init_meals: Initialise le mutex des repas
delete_philosophers: Nettoie les ressources des philosophes
is_philo_dead: Vérifie si un philosophe est mort (logiquement lié à leur cycle de vie)


philo_routine.c
Contient les fonctions qui définissent le comportement des philosophes:

philo_routine: Routine principale d'un philosophe
one_philo_routine: Cas spécial pour un seul philosophe
handle_action: Gère les actions (manger, dormir, penser)
increase_meals_nb: Compte les repas
get_meals_nb: Récupère le nombre de repas


philo_forks.c
Gestion des fourchettes:

lock_first_fork: Verrouille la première fourchette
lock_second_fork: Verrouille la deuxième fourchette
unlock_first_fork: Déverrouille la première fourchette
unlock_second_fork: Déverrouille la deuxième fourchette


dinner_init.c
Initialisation du dîner:

init_dinner: Initialise la structure du dîner
set_dinner: Configure les paramètres du dîner
init_forks: Initialise les fourchettes
delete_dinner: Nettoie les ressources du dîner
destroy_forks: Détruit les mutex des fourchettes


dinner_monitor.c
Surveillance du dîner:

monitor_dinner: Surveille l'état des philosophes
set_dinner_end: Termine le dîner
get_in_progress: Vérifie si le dîner est en cours
init_set_end: Initialise le mutex de fin
init_print: Initialise le mutex d'impression


dinner_status.c
Gestion de l'état du dîner:

init_is_full: Initialise le mutex de satiété
set_is_full: Marque un philosophe comme rassasié
init_meal_time: Initialise le mutex du temps de repas
set_meal_time: Définit le temps du dernier repas
get_meal_time: Récupère le temps du dernier repas


dinner_utils.c
Utilitaires pour le dîner:

get_is_full: Vérifie si un philosophe est rassasié
init_all_mutex: Initialise tous les mutex
free_all_mutex: Libère tous les mutex
init_forks_var: Initialise les variables des fourchettes
free_forks_var: Libère les variables des fourchettes


mutex_utils.c
Utilitaires pour les mutex:

handle_lock_mutex: Verrouille un mutex avec gestion d'erreur
handle_unlock_mutex: Déverrouille un mutex avec gestion d'erreur
print_died: Affiche qu'un philosophe est mort
check_str: Utilitaire pour comparer des chaînes


time_utils.c
Utilitaires pour la gestion du temps:

get_current_time_ms: Obtient le temps actuel en millisecondes
get_time_from_start: Calcule le temps écoulé depuis le début
get_current_time_usec: Obtient le temps actuel en microsecondes
safe_usleep: Endort un thread de manière sécurisée
safe_quick_usleep: Version optimisée pour de courts délais