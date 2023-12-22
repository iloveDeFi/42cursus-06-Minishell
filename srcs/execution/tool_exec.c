#include "minishell.h"

void free_split(char **arr)
{
    if (arr == NULL)
        return;

    int i = 0;
    while (arr[i] != NULL) {
        free(arr[i]);
        i++;
    }

    free(arr);
}

t_env *ft_copy_env_list(t_env *src)
{
    t_env *new_list = NULL;
    t_env *last = NULL;

    while (src != NULL)
    {
        t_env *new_node = create_node2(src->var, src->value);
        if (new_node != NULL)
        {
            if (last == NULL)
                new_list = new_node;
            else
                last->next = new_node;

            last = new_node;
        }
        src = src->next;
    }

    return new_list;
}

// Modifier la fonction create_node2 dans tool_exec.c
t_env *create_node2(char *var, char *value)
{
    t_env *new_node;
    new_node = malloc(sizeof(t_env));

    if (new_node)
    {
        new_node->var = ft_strdup(var);
        new_node->value = ft_strdup(value); // Assurez-vous que value est une chaîne de caractères
        new_node->next = NULL;
        return new_node;
    }
    return NULL;
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size) 
{
    char *ptr_char;
    void *new_ptr;
    char *new_ptr_char;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    if (ptr != NULL && new_ptr != NULL) 
    {
        size_t copy_size = old_size;
        if (new_size < old_size) 
            copy_size = new_size;
        new_ptr_char = (char *)new_ptr;
        ptr_char = (char *)ptr;

        size_t i = 0;
        while (i < copy_size) 
        {
            new_ptr_char[i] = ptr_char[i];
            i++;
        }
        free(ptr);
    }
    return new_ptr;
}



