#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <thread_db.h>
#include <unistd.h>

#define PORT_NUMBER 5231
#define BACK_LOG 256

#define IMGK_PATH "/usr/include/ImageMagick-6/"
#define ROOT "/home/giorgia/CLionProjects/WebServer/resources"
#define CACHE_ROOT "/home/giorgia/CLionProjects/WebServer/CACHE_DIR"
#define LOG_DIR "/home/giorgia/CLionProjects/WebServer/LOG/log.txt"

#define MAX_MSG 4096
#define BUFFER_SIZE 8096
#define HMAP_SIZE 164
#define LOGBUF_SIZE 100

#define TLOG_SLEEP 30
#define TCACHE_SLEEP 30


