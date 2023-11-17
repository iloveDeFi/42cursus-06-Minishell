#include "minishell.h"

// ...

t_global *create_global() {
    t_global *new_global = malloc(sizeof(t_global));

    if (new_global != NULL) {
        new_global->envVars = create_envVarList();  // Créez et initialisez la liste ici, s'il y a une fonction dédiée
        // Initialiser les autres membres de la structure t_global
    }

    return new_global;
}

// Fonction pour créer et initialiser une liste d'envVar
t_envVarList *create_envVarList() {
    t_envVarList *new_list = malloc(sizeof(t_envVarList));

    if (new_list != NULL) {
        new_list->length = 0;
        new_list->head = NULL;
        new_list->tail = NULL;
    }

    return new_list;
}
