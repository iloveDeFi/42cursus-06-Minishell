#include "minishell.h"

void test_expand_single_variable() {
    char *input;
    char *expected;
    char *result;

    // Test 1: Expansion d'une variable d'environnement simple
    input = "echo $HOME";
    expected = "echo /your/home/path";  // Remplacer par la valeur réelle de $HOME
    result = expand_single_variable(input, 0);
    if (strcmp(result, expected) == 0) {
        printf("Test 1 réussi\n");
    } else {
        printf("Test 1 échoué: Attendu '%s', Obtenu '%s'\n", expected, result);
    }
    free(result);

    // Test 2: Expansion de $? pour un code de sortie réussi
    input = "echo $?";
    expected = "echo 0";  // Supposons que le dernier code de sortie est 0
    result = expand_single_variable(input, 0);
    if (strcmp(result, expected) == 0) {
        printf("Test 2 réussi\n");
    } else {
        printf("Test 2 échoué: Attendu '%s', Obtenu '%s'\n", expected, result);
    }
    free(result);

    // Ajouter d'autres tests selon les besoins...
}

int main() {
    test_expand_single_variable();
    // Autres tests ou logique du programme...
    return 0;
}