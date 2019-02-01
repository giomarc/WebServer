#include "format.h"
#include "cache.h"
#include "configuration.h"
#include "file.h"
#include "content_adaptation.h"


/*
 * calls ImageMagick APIs to convert an image
 */
void convert_image_by_quality(char *filepath, char * q, char *adapted_filepath)
{
    errno = 0;
    char quality[4];
    sprintf(quality, "%1.f%%",100*cast_to_float(q));
    char *args = alloc_string(64);
    sprintf(args, "convert -quality %s %s %s", quality, filepath,adapted_filepath);
    //printf("%s\n",args);
    FILE *f = popen(args,"r");
    if(f == NULL)
    {
        perror("popen");
        exit(1);
    }
    pclose(f);
    free(args);
    return;
}


/*
 * creates the new name path for file to be converted
 */
void normalize_filename_img(char *new_path,char *originalpath, char *q, char *w, char *h)
{
    strcat(new_path,CACHE_ROOT);
    strcat(new_path,originalpath);
    char *a = strstr(new_path,".jpg");

    if((strcmp(w,"") == 0 && strcmp(h,"") == 0) && strcmp(q,"") !=0)
    {
        sprintf(a,"_%s.jpg",q);
    }
    else if(strcmp(w,"") == 0 && strcmp(h,"") == 0 && strcmp(q,"") ==0){

        return;
    }
    else
    {
        sprintf(a,"_%s_%s_%s.jpg",q,w,h);
    }
}

