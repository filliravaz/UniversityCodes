#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void backtrack(int pos, int sum, int count, int* current, int* best_count, int* best_sol, const int* pacchi, size_t n, int p) {
    if (pos == n) {
        if (count > *best_count) {
            *best_count = count;
            memcpy(best_sol, current, n * sizeof(int));
        }
        return;
    }

    // Prova a includere il pacco corrente
    if (sum + pacchi[pos] <= p) {
        current[pos] = 1;
        int new_sum = sum + pacchi[pos];
        int new_count = count + 1;
        int remaining = n - pos - 1;
        if (new_count + remaining > *best_count) {
            backtrack(pos + 1, new_sum, new_count, current, best_count, best_sol, pacchi, n, p);
        }
        current[pos] = 0; // Backtrack
    }

    // Prova a escludere il pacco corrente
    int remaining = n - pos - 1;
    if (count + remaining > *best_count) {
        backtrack(pos + 1, sum, count, current, best_count, best_sol, pacchi, n, p);
    }
}

void BabboNatale(const int* pacchi, size_t pacchi_size, int p) {
    if (pacchi_size == 0 || p < 0) return;

    int* current = calloc(pacchi_size, sizeof(int));
    int* best_sol = calloc(pacchi_size, sizeof(int));
    if (!current || !best_sol) {
        free(current);
        free(best_sol);
        return;
    }

    int best_count = -1;
    backtrack(0, 0, 0, current, &best_count, best_sol, pacchi, pacchi_size, p);

    if (best_count >= 0) {
        for (size_t i = 0; i < pacchi_size; ++i) {
            printf("%d", best_sol[i]);
            if (i != pacchi_size - 1) printf(" ");
        }
        printf("\n");
    }

    free(current);
    free(best_sol);
}
