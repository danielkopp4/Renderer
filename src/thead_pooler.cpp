#include "thread_pooler.hpp"
#include <iostream>
#include <chrono>

ThreadPooler::ThreadPooler(int allowed_threads_) : allowed_threads(allowed_threads_) {
    list_in_use = false;

    threads = new std::thread*[allowed_threads];
    for (unsigned int i = 0; i < allowed_threads; i++) {
        threads[i] = NULL;
        avalible_ids.push_back(i);
    } 
    current_threads = 0;
}

ThreadPooler::~ThreadPooler() {
    delete_all_threads();
    delete [] threads;
}

unsigned int ThreadPooler::next_id() {
    while (list_in_use) {
        // std::cout << "in use" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // std::cout << "locking" << std::endl;

    list_in_use = true;

    mutex.lock();
    unsigned int id = avalible_ids.front(); 
    // try {
        avalible_ids.pop_front();
    // } catch (int e) {
    //     list_in_use = false;
    //     std::cout << "ERROR " << e << std::endl;
    //     return next_id();
    // }
    mutex.unlock();
     
    list_in_use = false;
    return id;
}


void ThreadPooler::delete_all_threads() {
    for (unsigned int i = 0; i < allowed_threads; i++) {
        std::thread* ptr_cpy = threads[i];
        threads[i] = NULL;

        if (ptr_cpy != NULL) {            
            if (ptr_cpy->joinable()) {
                ptr_cpy->join();
            }

            delete ptr_cpy;
        }
    }
}

void ThreadPooler::wait_to_finish() {
    for (unsigned int i = 0; i < allowed_threads; i++) {
        if (threads[i] != NULL) {            
            if (threads[i]->joinable()) {
                threads[i]->join();
            }
        }
    }
}

void ThreadPooler::add_thread(Renderer* renderer, int i, int j, int samples) {
    while (avalible_ids.size() < 1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    // std::cout << i << " " << j << std::endl;
    // std::cout << avalible_ids.size() << std::endl;


    unsigned int id = next_id();
    // std::cout << "giving id " << id  << std::endl;
    // std::cout << avalible_ids.size()<< " vs " << () << std::endl;
    std::thread* new_thread = new std::thread(&Renderer::add_pixel, renderer, i, j, samples, id);
    // new_thread->detach();
    if (threads[id] != NULL) {
        // std::cout << avalible_ids.size() - current_threads << std::endl;
        if (threads[id]->joinable()) {
            // std::cout << "EEeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeEP" << std::endl;
            threads[id]->join();
        }
        delete threads[id];
    }

    threads[id] = new_thread;
    current_threads++;
}

void ThreadPooler::finish_thread(unsigned int id) {
    // std::cout << "finsihed id: " << id << std::endl;
    while (list_in_use) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // do i need this if so decrease time
    }
    list_in_use = true;
    mutex.lock();
    avalible_ids.push_back(id);
    mutex.unlock();
    list_in_use = false;
    current_threads--;
} 
