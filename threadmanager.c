#include "threadmanager.h"
#include "thread_connection_job.h"
#include "http_request.h"
#include "cache.h"
#include "configuration.h"


//returns new node pointer
struct thread_node* alloc_node()
{
    struct thread_node *new;
    new = malloc(sizeof(struct thread_node *));

    if(new == NULL)
    {
        printf("Error allocating new thread node\n");
        exit(1);
    }
    return new;
}


//trova il primo thread libero cui associare il lavoro da fare per gestire la connessione
struct thread_node *find_not_busy_thread()
{
    struct thread_node *t;

    LIST_FOREACH(t,&head,pool)
    {
        if(t->busy == 0) return t;
    }
    return NULL;
}


//inizializzo la testa della lista
void initialize_head()
{
    LIST_INIT(&head);
}


//crea il pool di thread quando viene avviato il main
void fill_empty_pool()
{
    struct thread_node *before;
    int i =0;

    while(i<1000){

        struct thread_node *new;
        new = alloc_node();

        if(i==0)
        {
            pthread_create(&new->tid,NULL, accept_connection,(void *)new);
            LIST_INSERT_HEAD(&head,new,pool);
            printf("Created thread: %d\n",i);
        }
        else
        {
            pthread_create(&new->tid, NULL, accept_connection, (void *) new);
            new->busy = 0;
            LIST_INSERT_AFTER(before, new, pool);
            printf("Created thread: %d\n",i);
        }
        before = new;
        i++;
    }

    last = before;
    actual_pool_size +=i;
}

void increment_pool()
{
    int i = actual_pool_size, size = 2*actual_pool_size;
    struct thread_node *before = last;

    while(i < size)
    {
        struct thread_node *new;
        new = alloc_node();

        pthread_create(&new->tid, NULL, accept_connection, (void *) new);
        new->busy = 0;
        LIST_INSERT_AFTER(before, new, pool);

        before = new;
        ++i;
    }

    last = before;
    actual_pool_size = i;
}

//elimina alcuni nodi del pool quando il carico è basso
void reduce_pool(int to_delete)
{
    struct thread_node *p = LIST_FIRST(&head);
    int count_deleted = 0;

    while (count_deleted <= to_delete && p!=NULL)
    {
        struct thread_node *next = LIST_NEXT(p,pool);
        free(p);
        count_deleted++;
        p = next;
    }

    LIST_INIT(&head);
}


void initialize_cond()
{
    if(pthread_cond_init(&connection_available,NULL)!=0)
    {
        printf("Error initializing condition");
        exit(1);
    }

}


void initialize_mtx()
{
    if(pthread_mutex_init(&t_job_mtx, NULL)!=0)
    {
        printf("Error initializing mutex\n");
        exit(1);
    }

}


