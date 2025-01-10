#include <mpi.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric> // for std::iota
#include <random> // for random number generation

// Funktion zum Mergen zweier sortierter Vektoren
std::vector<int> merge_sorted_blocks(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    result.reserve(left.size() + right.size());
    auto it1 = left.begin();
    auto it2 = right.begin();

    while (it1 != left.end() && it2 != right.end()) {
        if (*it1 < *it2) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    result.insert(result.end(), it1, left.end());
    result.insert(result.end(), it2, right.end());
    return result;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::vector<int>> test_cases;
    if (rank == 0) {
        // Generierung von Testfällen mit unterschiedlichen Größen >= 2^10
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::vector<int> sizes = {1 << 10, (1 << 10) + 500, (1 << 11), (1 << 11) + 300, (1 << 12)};
        for (int test_size : sizes) {
            std::vector<int> test_case(test_size);
            std::iota(test_case.begin(), test_case.end(), 0);
            std::shuffle(test_case.begin(), test_case.end(), rng);
            test_cases.push_back(test_case);
        }
    }

    for (const auto& test_case : test_cases) {
        const int N = test_case.size();
        std::vector<int> input;
        std::vector<int> local_block;

        // Wurzelprozess erstellt das Eingabearray
        if (rank == 0) {
            input = test_case;
        }

        // Verteilung der Blockgrößen
        int block_size = N / size;
        int remainder = N % size;
        std::vector<int> sendcounts(size, block_size);
        std::vector<int> displs(size, 0);

        for (int i = 0; i < remainder; ++i) {
            sendcounts[i]++;
        }

        for (int i = 1; i < size; ++i) {
            displs[i] = displs[i - 1] + sendcounts[i - 1];
        }

        local_block.resize(sendcounts[rank]);

        // Verteilung der Blöcke an Prozesse
        MPI_Scatterv(input.data(), sendcounts.data(), displs.data(), MPI_INT,
                     local_block.data(), sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

        // Sortierung der lokalen Blöcke
        std::sort(local_block.begin(), local_block.end());

        // Sammeln der sortierten Blöcke
        std::vector<int> gathered_data;
        if (rank == 0) {
            gathered_data.resize(N);
        }

        MPI_Gatherv(local_block.data(), sendcounts[rank], MPI_INT,
                    gathered_data.data(), sendcounts.data(), displs.data(), MPI_INT, 0, MPI_COMM_WORLD);

        // Zusammenführung der sortierten Blöcke (nur Wurzelprozess)
        if (rank == 0) {
            std::vector<int> sorted_array = gathered_data;

            // Merge sortierte Blöcke schrittweise zusammenführen
            for (int i = 1; i < size; ++i) {
                std::vector<int> next_block(sorted_array.begin() + displs[i], sorted_array.begin() + displs[i] + sendcounts[i]);
                sorted_array = merge_sorted_blocks(sorted_array, next_block);
            }

            // Ergebnis ausgeben
            std::cout << "Testfall mit " << N << " Elementen: ";
            if (std::is_sorted(sorted_array.begin(), sorted_array.end())) {
                std::cout << "Array ist korrekt sortiert!\n";
            } else {
                std::cout << "Fehler: Array ist nicht sortiert.\n";
            }
        }
    }

    MPI_Finalize();
    return 0;
}

