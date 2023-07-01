#include <iostream>
#include <windows.h>

// Thread function
DWORD WINAPI parallelFunction(LPVOID lpParam) {
    int id = (int)lpParam;
    std::cout << "Thread " << id << " started." << std::endl;

    // Parallel computation
    for (int i = 0; i < 10; i++) {
        // Acquire the mutex before printing
        std::cout << "Thread " << id << " is processing iteration " << i << std::endl;
        // Release the mutex after printing
    }

    std::cout << "Thread " << id << " finished." << std::endl;
    return 0;
}

int main() {
    int numThreads;
    std::cout << "Enter the number of threads to use: ";
    std::cin >> numThreads;

    HANDLE threads[numThreads];
    int threadIds[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i;
        threads[i] = CreateThread(NULL, 0, parallelFunction, &threadIds[i], 0, NULL);
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < numThreads; i++) {
        CloseHandle(threads[i]);
    }
    return 0;
}