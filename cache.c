#include "file.h"
#include "format.h"
#include "configuration.h"
#include "content_adaptation.h"
#include "cache.h"
#include "log.h"

pthread_mutex_t cache_mtx = PTHREAD_MUTEX_INITIALIZER;


/**
 * creates thread that must clean cache
 */
void create_thread_cache(struct Hashmap *hmap)
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, clean_hashmap, (void *) hmap)!=0)
    {
        perror("thread cache");
        exit(1);
    }
}


/*
 * cleans hashmap node of the file less used
 */
void * clean_hashmap(void * map)
{
    struct Hashmap *hmap = (struct Hashmap*) map;
    char *args = calloc(1,128*sizeof(char));
    while(1)
    {
        sleep(30);
        lock_cache_mtx();
        int min_usage = 10000;
        int i = 0;
        int j = 0;
        int elem_to_delete;
        char *msg_log = alloc_string(128);
        while(j < hmap->element_count && i < HMAP_SIZE) {

            //finding less usage
            if (hmap->node_list[i] != NULL) {
                if (min_usage > hmap->node_list[i]->usage) {
                    min_usage = hmap->node_list[i]->usage;
                    elem_to_delete = i;
                }
                j++;
            }
            i++;
        }
        //if there are no more files break
        if(hmap->node_list[elem_to_delete] == NULL)
        {
            break;
        }
        else
        {

            sprintf(args,"rm %s",hmap->node_list[elem_to_delete]->value);
            FILE * f= popen(args,"r");
            pclose(f);
            memset(hmap->node_list[elem_to_delete]->value,0,sizeof(hmap->node_list[elem_to_delete]->value));
            hmap->node_list[elem_to_delete]->usage = 0;
            memset(hmap->node_list[elem_to_delete],0,sizeof(hmap->node_list[elem_to_delete]));
            hmap->node_list[elem_to_delete] = NULL;
            hmap->element_count--;
        }
        unlock_cache_mtx();
        sprintf(msg_log,"[CACHE]\n%s\n",args+3);
        write_on_buffer(msg_log);
        free(msg_log);
    }
}


/*
 * destroys hashmap
 */

void destroy_hashmap(struct Hashmap *hmap)
{
    int i;

    for(i= 0; i < hmap->element_count; i++)
    {
        free(hmap->node_list[i]);
    }

    free(hmap);
}


/*
 * creates a new HashmapNode and sets node values
 */
struct HashmapNode *hashmap_new_node(int key, char *value)
{
    struct HashmapNode  *h_node = malloc(sizeof(struct HashmapNode*));

    h_node->key = key;
    h_node->value = alloc_string(128);
    h_node->usage = 1;
    strcat(h_node->value,value);

    return h_node;
}



/*
 * initialized the hashmap
 */
struct Hashmap *create_hashmap()
{
    int i;
    struct Hashmap *hmap = (struct Hashmap *) malloc(sizeof(struct Hashmap));

    if(hmap == NULL)
    {
        perror("malloc hashmap");
        exit(1);
    }

    hmap->node_list = malloc(HMAP_SIZE*sizeof(struct HashmapNode));
    if(hmap->node_list == NULL)
    {
        perror("malloc node_list");
        exit(1);
    }

    hmap->element_count = 0;

    for(i = 0; i < HMAP_SIZE; i++)
    {
        hmap->node_list[i] = malloc(sizeof(struct HashmapNode));
        hmap->node_list[i] = NULL;


    }
    return hmap;
}


/**
 * creates hashmap item index
 */
int  hashmap_func(char *filename, char *q, char *w, char *h)
{
    int fw,fh,ff;
    int fq = (int) (cast_to_float(q)*100);

    if(strcmp(w,"")== 0 && strcmp(h,"") == 0)
    {
        fw = fh = 1;
    }
    else
    {
        fw = cast_to_int(w);
        fh = cast_to_int(h);
    }
    int hash = (filename[1] +((fq * fw) / fh))%64;
    return hash;
}


/*
 * finds a node into the hashmap given the key
 *la chiave viene calcolata a partire dal path del file
 */
int hashmap_search_item(char *filefound,struct Hashmap *hmap,char *filename, char *q, char *w, char *h)
{
    int hash = hashmap_func(filename,q,w,h);
    lock_cache_mtx();
    if(hmap->node_list[hash] == NULL)
    {
        unlock_cache_mtx();
        return -1; //file not found
    }
    else
    {
        strcat(filefound,hmap->node_list[hash]->value);
        hmap->node_list[hash]->usage++;
        unlock_cache_mtx();
        return 0;
    }
}


/*
 * inserts new node into hasmap
 * step1: create key
 * step2: init value to filepath
 * step3: increment num of
 */
void insert_in_hashmap(struct Hashmap *hmap,char *filename, char *q, char *w, char *h, char *value,char *originalpath)
{
    int hash = hashmap_func(filename,q,w,h);

    if(hmap->node_list[hash] != NULL && hmap->node_list[hash]->key == hash)
    {
        printf("Found collision\n");
        return;
    }
    else
    {
        lock_cache_mtx();
        normalize_filename_img(value, filename, q, "", "");
        convert_image_by_quality(originalpath, q, value);
        hmap->node_list[hash] = hashmap_new_node(hash, value);
        hmap->element_count++;
        unlock_cache_mtx();
    }
}



void lock_cache_mtx(void)
{
    if(pthread_mutex_lock(&cache_mtx)!=0)
    {
        perror("lock log mtx");
        exit(1);
    }
}

void unlock_cache_mtx(void)
{
    if(pthread_mutex_unlock(&cache_mtx)!=0)
    {
        perror("lock log mtx");
        exit(1);
    }
}


