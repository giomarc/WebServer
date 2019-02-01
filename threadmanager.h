#ifndef threadmanager_h
#define threadmanager_h

#include "configuration.h"

pthread_cond_t connection_available;
pthread_mutex_t t_job_mtx;


int actual_pool_size;

LIST_HEAD(listhead,thread_node) head;

struct thread_node *last;

struct thread_node{
    pthread_t tid;
    int tconnsk;
    struct sockaddr *clientaddr;
    pthread_mutex_t t_job_mutex;
    int busy;
    char req_filepath[128];
    LIST_ENTRY(thread_node) pool;
    struct Hashmap *h_map;
};



struct thread_node* alloc_node();
struct thread_node *find_not_busy_thread();
void initialize_head();
void fill_empty_pool();
void reduce_pool(int);
void initialize_head();
void initialize_cond();
void initialize_mtx();
void increment_pool();

#endif