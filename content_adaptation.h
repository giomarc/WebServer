#ifndef content_adaptation_h
#define content_adaptation_h


void convert_image_by_quality(char *filepath, char * q, char *adapted_filepath);
void normalize_filename_img(char *new_path, char *originalpath, char *q, char *w, char *h);

#endif