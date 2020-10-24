#ifndef __thread_pooler_hpp_
#define __thread_pooler_hpp_

#include <list>
#include <thread>
#include <mutex>
#include "renderer.hpp"

const unsigned int DEFAULT_THREAD_VARIANCE = 50;

class Renderer;
class ThreadPooler {
private:
    unsigned int allowed_threads;
    unsigned int current_threads;
    std::thread** threads;
    std::mutex mutex;
    std::list<unsigned int> avalible_ids;
    bool list_in_use;
    unsigned int next_id();
    void delete_all_threads();
public:
    ThreadPooler(int alllowed_threads_=(std::thread::hardware_concurrency() - DEFAULT_THREAD_VARIANCE));
    ~ThreadPooler();
    void add_thread(Renderer* renderer, int i, int j, int samples);
    void wait_to_finish();
    void set_allowed_threads(unsigned int allowed_threads_) { allowed_threads = allowed_threads_; }
    void finish_thread(unsigned int id);
    
};



#endif
