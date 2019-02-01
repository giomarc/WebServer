#include "configuration.h"
#include "format.h"

/*
 * retrieves file size
 */
long int get_file_size(char *filename)
{
    int size_of_file;
    struct stat st_file;
    stat(filename,&st_file);
    size_of_file = st_file.st_size;
    return size_of_file;
}

//false = 0
//true  = !=0
/*
 * checks if file exists
 */
int exist_file(char *path)
{
    struct stat st;
    return stat(path, &st);
}

/*
 * builds filepath
 */
char *get_file_path(char *filename,char *fullpath)
{
    sprintf(fullpath,"%s%s",ROOT,filename);
}

