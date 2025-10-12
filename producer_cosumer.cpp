#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <semaphore.h>

using namespace std;
//First we need a buffer to hold values
queue<int> buffer;
mutex mtx;
condition_variable cv;
sem_t emptySlots;
sem_t fullSlots;

void produce_sem(){
    //Say we're producing 5 at a time
    for (int ii = 1; ii <= 5; ++ii){
        sem_wait(&emptySlots);
        buffer.push(ii);
        cout << "Produced: " << ii << endl;
        sem_post(&fullSlots);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consume_sem(){
    while (true){
            sem_wait(&fullSlots);
            int data = buffer.front();
            buffer.pop();
            cout << "Cosumed: " << data << endl;
            sem_post(&emptySlots);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void produce(){
    //Say we're producing 5 at a time
    for (int ii = 1; ii <= 5; ++ii){
        //First get a lock
        std::lock_guard<std::mutex> lock(mtx);
        buffer.push(ii);
        cout << "Produced: " << ii << endl;
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
}
void consume(){
        while (true){
            //First get a lock
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] {return !buffer.empty();});
            int data = buffer.front();
            buffer.pop();
            cout << "Cosumed: " << data << endl;
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
}

//Another implementation: https://medium.com/nerd-for-tech/hands-on-multithreading-with-c-04-producer-consumer-problem-26abdddc485d

std::mutex mtx; // Mutex for synchronization
std::condition_variable cond_var; // Condition variable for producer-consumer signaling
std::queue<int> buffer; // Queue to act as a buffer
const unsigned int MAX_BUFFER_SIZE = 10; // Maximum size of the buffer
void producer_t(int value) {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    cond_var.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; }); // Wait until there's space in buffer
    buffer.push(value); // Add value to the buffer
    std::cout << "Producing " << value << std::endl; // Output the produced value
    std::cout << "Buffer size after producing: " << buffer.size() << std::endl << std::endl; // Display buffer size after producing
    lock.unlock(); // Unlock the mutex
    cond_var.notify_one(); // Notify one waiting thread
}
void consumer_t() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    cond_var.wait(lock, [] { return buffer.size() > 0; }); // Wait until there's something in the buffer
    int value = buffer.front(); // Get the front value from buffer
    buffer.pop(); // Remove the value from buffer
    std::cout << "Consuming " << value << std::endl; // Output the consumed value
    std::cout << "Buffer size after consuming: " << buffer.size() << std::endl << std::endl; // Display buffer size after consuming
    lock.unlock(); // Unlock the mutex
    cond_var.notify_one(); // Notify one waiting thread
}


int main(){

    //sem_init(&emptySlots, 0, 5);  // Maximum 5 empty slots in the buffer
    //sem_init(&fullSlots, 0, 0); // Initially, no full slots in the buffer

    thread producer(produce);
    thread consumer(consume);
    // producer.join();
    // consumer.join();

    //thread producer (produce_sem);
    //thread consumer(consume_sem);
    producer.join();
    consumer.join();

    //sem_destroy(&emptySlots);
    //sem_destroy(&fullSlots);

    return 0;
}
