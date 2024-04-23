#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    bool swapped;

    auto start_parallel = high_resolution_clock::now(); // Start measuring parallel Bubble Sort execution time

    for (int i = 0; i < n - 1; ++i)
    {
        swapped = false;
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    auto stop_parallel = high_resolution_clock::now(); // Stop measuring parallel Bubble Sort execution time
    auto duration_parallel = duration_cast<milliseconds>(stop_parallel - start_parallel);
    cout << "Parallel Bubble Sort completed in " << duration_parallel.count() << " milliseconds.\n";
}

void sequentialBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    bool swapped;

    auto start_sequential = high_resolution_clock::now(); // Start measuring sequential Bubble Sort execution time

    for (int i = 0; i < n - 1; ++i)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    auto stop_sequential = high_resolution_clock::now(); // Stop measuring sequential Bubble Sort execution time
    auto duration_sequential = duration_cast<milliseconds>(stop_sequential - start_sequential);
    cout << "Sequential Bubble Sort completed in " << duration_sequential.count() << " milliseconds.\n";
}

int main()
{
    // Generate random input data
    int n = 10000;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 1000;
    }

    // Perform Bubble Sort
    cout << "Sequential Bubble Sort:" << endl;
    sequentialBubbleSort(arr);

    cout << "\nParallel Bubble Sort:" << endl;
    parallelBubbleSort(arr);

    return 0;
}