#include <string.h>
#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include "libwurfl/src/wurfl.h"
#include "libwurfl/src/device.h"


wurfl_t *wurfl;

void initialize_wurfl(void)
{

    const char* patches[] = {NULL};
    wurfl = wurfl_init("../etc/wurfl.xml",patches);
}



void get_wurfl_values(char *user_agent, char *w, char *h)
{
    device_t* device = wurfl_match(wurfl,user_agent);
    char **capabilities = device_capabilities(device,NULL);
    char **caps_ptr = capabilities;

    while(caps_ptr != NULL && *caps_ptr!=NULL)
    {
        if(strcmp(*caps_ptr,"resolution_width") ==0)
        {
            sprintf(w,"%s",*(caps_ptr+1));
        }
        else if(strcmp(*caps_ptr,"resolution_height") == 0)
        {
            sprintf(h,"%s",*(caps_ptr +1));
        }
        caps_ptr+=2;
    }
}