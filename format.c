#include "format.h"
#include "configuration.h"

/*
 * casts a string to float
 */
float cast_to_float(char *value)
{
    char *p;
    errno = 0;
    float v = (float) strtof(value,&p);

    if(errno!=0 && *p != '\0')
    {
        perror("strtof ");
        exit(EXIT_FAILURE);
    }

    return v;
}


/*
 * casts a string to int
 */
int cast_to_int(char *value)
{
    char *p;
    errno = 0;
    int v = (int) strtol(value,&p,0);

    if(errno!=0 && *p != '\0')
    {
        perror("strtol ");
        exit(EXIT_FAILURE);
    }

    return v;
}


/*
 * creates dynamic memory for a string
 */
char *alloc_string(int size)
{
    char *s = calloc(size,sizeof(char)*size);

    if(s == NULL)
    {
        perror("calloc");
        exit(1);
    }

    return s;
}

