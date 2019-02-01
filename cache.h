#ifndef cache_h
#define cache_h

#include <pthread.h>

//#define HMAP_SIZE 164
extern pthread_mutex_t cache_mtx;


struct HashmapNode
{
    int key; //chiave ottenuta tramite q,w,h,filename
    char *value; //path file
    int usage; //fattore di utilizzo del file
    struct HashmapNode *next;
};

struct Hashmap{
    int element_count; //numero chiavi inserite
    struct HashmapNode **node_list;
};

struct HashmapNode * hashmap_new_node(int key, char *value);
struct Hashmap * create_hashmap();
int hashmap_func(char *filename, char *q, char *w, char *h);
int hashmap_search_item(char *filefound,struct Hashmap *hmap, char *filename, char *q, char *w, char *h);
void insert_in_hashmap(struct Hashmap *hmap, char *filename, char *q, char *w, char *h, char *value,char *originalpath);
void destroy_hashmap(struct Hashmap *hmap);
void lock_cache_mtx(void);
void unlock_cache_mtx(void);
void * clean_hashmap(void * map);
void create_thread_cache(struct Hashmap *hmap);

#endif