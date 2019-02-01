#ifndef log_h
#define log_h

#include <pthread.h>


int buf_index;
extern pthread_mutex_t log_mtx;

struct buffer_log_node{
    char *msg;
};
struct buffer_log_node *logbuf[100];


void init_log_mtx();
void lock_log_mtx();
void unlock_log_mtx();
void create_threadlog();
void init_log_cond();


int open_log();
void * write_log(void *log);
void init_logbuf();
void write_on_buffer(char *);
void display_log();





#endif