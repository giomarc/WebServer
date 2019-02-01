#include "log.h"
#include "http_request.h"
#include "configuration.h"


pthread_mutex_t log_mtx = PTHREAD_MUTEX_INITIALIZER;


/*
 * initializes mutex used to write into log buffer
 */
void init_log_mtx()
{
    if(pthread_mutex_init(&log_mtx, NULL)!=0)
    {
        printf("Error initializing mutex\n");
        exit(1);
    }
}


/*
 * to lock the log mutex
 */
void lock_log_mtx()
{
    //il thread prende il mutex prima di scrivere nel buffer
    if(pthread_mutex_lock(&log_mtx)!=0)
    {
        perror("log mtx lock");
        exit(1);
    }
}


/*
 * to unlock the log mutex
 */
void unlock_log_mtx()
{
    if(pthread_mutex_unlock(&log_mtx)!=0)
    {
        perror("log mtx unlock");
        exit(1);
    }
}


/*
 * threads use this function to write on buffer log
 */
void write_on_buffer(char *msg)
{
    lock_log_mtx();

    if(buf_index < 80)
    {
        strcat(logbuf[buf_index]->msg,msg);
        buf_index++;
    }

    unlock_log_mtx();
}


/*
 * creates log buffer
 */
void init_logbuf()
{
    buf_index = 0;

    for(int i = 0; i < 100; i++)
    {
        logbuf[i] = malloc(sizeof(struct buffer_log_node));
        logbuf[i]->msg = calloc(1,1024*sizeof(char));
    }
}


/*
 * open/create log file
 */
int open_log()
{
    int log_fd = open(LOG_DIR,O_RDWR|O_CREAT|O_APPEND, 0666);

    if(log_fd == -1)
    {
        perror("open log for threadlog");
        exit(1);
    }
    return log_fd;
}


/*
 * thread log function to write buffer messages into file
 */
void * write_log(void *log)
{
    int fd = open_log();

    while(buf_index < 80) //se il carico è pesante, evito la scrittura sul file dei log
    {
        sleep(TCACHE_SLEEP);
        lock_log_mtx();

        for(int i = 0; i<buf_index;i++)
        {
            write(fd,logbuf[i]->msg,strlen(logbuf[i]->msg));
            memset(logbuf[i]->msg,0,sizeof(logbuf[i]->msg));
        }
        buf_index = 0;
        unlock_log_mtx();
    }
}


/*
 * creates thread that will write on file log
 */

void create_threadlog()
{
    pthread_t tid;

    if(pthread_create(&tid,NULL, write_log,(void *)NULL)!=0)
    {
        perror("create threadlog");
        exit(1);
    }
}

