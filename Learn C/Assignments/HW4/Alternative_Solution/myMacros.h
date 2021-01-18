#pragma once

#define DETAIL_PRINT

typedef  unsigned char BYTE;

#define ERROR 0
#define FROM_FILE 1
#define FROM_USER 2


#define CHECK_RETRUN_0(value) if(value==NULL){return 0;}
#define CHECK_RETURN_NULL(value) if(value==NULL){return NULL;}
#define CHECK_MSG_RETURN_0(value,msg) if(value==NULL){puts(msg); return 0;}
#define CHECK_RETURN_0(value) if(value==NULL){return 0;}
#define CLEAN_BUFFER()	{getchar(); }
#define CHECK_0_MSG_CLOSE_FILE(value,fp,msg) if(value==0){fclose(fp); puts(msg);return 0;}
#define CHECK_NULL_MSG_COLSE_FILE(value,fp,msg) if(value==NULL){puts(msg); fclose(fp);return 0;}
#define MSG_CLOSE_RETURN_0(fp,msg) {puts(msg); fclose(fp);return 0;}
#define MSG_CLOSE_RETURN_NULL(fp,msg) {puts(msg); fclose(fp);return NULL;}

#define ERROR_MSG_PAUSE_RETURN_0(msg)  { puts(msg); system("pause");return 0;}
