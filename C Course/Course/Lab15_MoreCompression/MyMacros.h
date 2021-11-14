#pragma once

typedef unsigned char BYTE;

#define CHECK_RETURN_NULL(value)            if(value==NULL){return NULL;}
#define CHECK_RETURN_0(value)                if(value==NULL){return 0;}


#define CHECK_NULL_CLOSE_FILE(value, file)    if(value==NULL){fclose(file);return NULL;}
#define CHECK_NULL_CLOSE_FILE_0(value, file) if(value==NULL){fclose(file);return 0;}
#define CHECK_NULL_FREE_CLOSE_FILE(value, ptr, file) if(value==NULL){free(ptr);fclose(file);return NULL;}
