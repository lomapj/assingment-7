#include <pthread.h>
#include <iostream>
#include <unistd.h>  // For sleep()

// Shared data and mutex declaration
int sharedData = 0;
pthread_mutex_t mutex;

void* writerThread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);       // Lock the mutex before writing
        sharedData = i;
        std::cout << "Thread_1 wrote: " << sharedData << std::endl;
        pthread_mutex_unlock(&mutex);     // Unlock the mutex after writing
        sleep(1); // Simulate some delay
    }
    pthread_exit(nullptr);
}

void* readerThread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex);       // Lock the mutex before reading
        std::cout << "Thread_2 read: " << sharedData << std::endl;
        pthread_mutex_unlock(&mutex);     // Unlock the mutex after reading
        sleep(1); // Simulate some delay
    }
    pthread_exit(nullptr);
}

int main() {
    // Initialize the mutex
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
        std::cerr << "Mutex initialization failed!" << std::endl;
        return 1;
    }

    pthread_t t1, t2;

    // Create writer and reader threads
    pthread_create(&t1, nullptr, writerThread, nullptr);
    pthread_create(&t2, nullptr, readerThread, nullptr);

    // Wait for both threads to finish execution
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    // Destroy the mutex after use
    pthread_mutex_destroy(&mutex);

    return 0;
}
