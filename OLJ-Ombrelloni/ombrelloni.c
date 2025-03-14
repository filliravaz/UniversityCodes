#include <stdio.h>
#include <stdlib.h>

// Funzione di backtracking ricorsiva
void backtrack(int pos, int current_k, int prev_occupied, int* sol, int n, int k, int* count) {
    // Caso base: raggiunta la fine della fila
    if (pos == n) {
        // Controlla se abbiamo piazzato esattamente k amici
        if (current_k == k) {
            (*count)++; // Incrementa il conteggio delle soluzioni

            // Formattazione dell'output come richiesto
            printf("%4d) ", *count); // Numero soluzione con padding a 4 cifre

            // Stampa la sequenza di 0 e 1
            for (int i = 0; i < n; i++) {
                printf("%d", sol[i]);
                if (i != n - 1) printf(" "); // Spazi tra i numeri, tranne alla fine
            }
            printf("\n"); // A capo dopo ogni soluzione
        }
        return;
    }

    // Prova a mettere 0 (ombrellone libero)
    sol[pos] = 0;
    backtrack(pos + 1, current_k, 0, sol, n, k, count);

    // Prova a mettere 1 (amico) solo se il precedente è 0
    if (!prev_occupied) {
        sol[pos] = 1;
        backtrack(pos + 1, current_k + 1, 1, sol, n, k, count);
    }
}

int Ombrelloni(int k, int n) {
    // Controllo input non validi
    if (k < 0 || n < 0) return 0;

    // Caso speciale: fila vuota
    if (n == 0) {
        if (k == 0) {
            printf("   1) \n"); // Unica soluzione valida
            return 1;
        }
        return 0;
    }

    // Calcolo massimo amici possibili
    int max_possible = (n + 1) / 2;
    if (k > max_possible) return 0;

    // Allocazione memoria per la soluzione corrente
    int* sol = malloc(n * sizeof(int));
    if (!sol) return 0; // Controllo errore allocazione

    int count = 0; // Contatore soluzioni
    backtrack(0, 0, 0, sol, n, k, &count); // Avvia il backtracking

    free(sol); // Libera memoria
    return count;
}
