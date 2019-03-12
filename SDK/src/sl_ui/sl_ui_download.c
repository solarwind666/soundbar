#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <queue.h>
#include <fcntl.h>

pid_t g_down_pid = -1;

static char savpath[255];
static dq_queue_t filelist;
typedef struct Favdown_list {
    dq_entry_t node;
    char url[1024];
    int urllen;
}fav_down_list_t;

static char *strip_ext(char *name)
{
    char *period;

    period = strrchr(name, '.');
    if (period)
        *period = '\0';

    return period;
}

static char *get_path(char *name)
{
    char *period;

    period = strrchr(name, '/');
    if (period)
        *period = '\0';

    return period;
}

static char *get_file_extension (const char *filename)
{
  char *str = NULL;

  str = strrchr (filename, '.');
  if (str)
    str++;

  return str;
}

static char *get_file_name (const char *path)
{
  char *str = NULL;

  str = strrchr (path, '/');
  if (str)
    str++;

  return str;
}
static int fp;
static int quiting = 0;
static void callback(FAR char **buffer, int offset, int datend,
                     FAR int *buflen, FAR void *arg)
{
  (void)write(fp, &((*buffer)[offset]), datend - offset);
}

int downfile(char *url)
{
    char filename[256];
    char rec_name[256];
    char *pname;
    char *ext;
    char *ptr;
    int format;
    int filesize;
    void *ws;
    int size = 2048;
    char buffer[2048];
    int ret;
    int readed;
    int total_read = 0;
    pname = get_file_name(url);
    ext =  get_file_extension(pname);

    if (ptr = strrchr(url, '.')) {
        ptr++;
        if(strstr(ptr,"mp3"))       { format = 3;    }
        else if(strstr(ptr,"aac"))  { format = 3;    }
        else if(strstr(ptr,"wma"))  { format = 3;    }
        else if(strstr(ptr,"flac")) { format = 4;    }
        else if(strstr(ptr,"ape"))  { format = 3;     }
        else if(strstr(ptr,"ac3"))  { format = 3;     }
        else if(strstr(ptr,"dts"))  { format = 3;     }
        else if(strstr(ptr,"wav"))  { format = 3;     }
        else if(strstr(ptr,"ogg"))  { format = 3;     }
        else if(strstr(ptr,"m4a"))  { format = 3;     }
        else if(strstr(ptr,"ts"))   { format = 2;     }
        else                        { format = 0; }
    }
    memset(filename,0,sizeof(filename));
    strncpy(filename,pname,ext-pname+format);
    memset(rec_name,0,sizeof(rec_name));
    sprintf(rec_name,"%s/%s",savpath,filename);

    ws = wget_http_open(url, buffer, sizeof(buffer), callback, NULL, 0);
    if( ws == NULL) {
        printf("=============wget_http_open error\n");
        return 0;
    }
    fp = open(rec_name,O_RDWR|O_CREAT);
    if(fp < 0) {
        printf("=============open down recfile error: %s\n",rec_name);
        wget_http_close(ws);
        return -1;
    }
    filesize = wget_http_get_filesize(ws);
    //printf("=====filesize:%d\n",filesize);
    while (!quiting) {
        readed = wget_http_read(ws, buffer, size);
        if(readed <= 0) {
            printf("============wget_http_read len <=0\n");
            break;
        }
        usleep(5000);
        if(readed > 0) {
            ret = write(fp, buffer, readed);
            total_read +=readed;
        }
        if(total_read >= filesize) {
            printf("downlaod file:%s is ok!\n",rec_name);
            break;
        }
    }
    if (ws) {
        wget_http_close(ws);
    }
    close(fp);
    fp = -1;
    return 0 ;
}
static int download_entry( ) //int argc, FAR char *argv[])
{
    fav_down_list_t  *down_list;
    for(;;) {
        down_list = (fav_down_list_t *)dq_peek(&filelist);
        if(!down_list)
            break;
        //printf("-----geturl:%s\n",down_list->url);
        downfile(down_list->url);
        dq_rem(&down_list->node, &filelist);
        free(down_list);
    }
    g_down_pid = -1;
    return 0;
}

static int thread_init(void)
{
    g_down_pid = task_create("download", 5, 16384, download_entry, NULL);

    if (g_down_pid < 0) {
        printf("Failed to start task dowload_entry" );
        return -1;
    }

    return 0;
}

void setfav_down_url(char *url, char *path)
{

    fav_down_list_t  *down_list;
    down_list = malloc(sizeof(fav_down_list_t));
    if(down_list == NULL) {
        printf("======%s malloc is error\n",__func__);
        return -1;
    }
    memset(savpath,0,sizeof(savpath));
    strcpy(savpath,path);
    memset(down_list,0,sizeof(fav_down_list_t));
    strcpy(down_list->url,url);
    down_list->urllen = strlen(url);
    if(g_down_pid < 0)
        dq_init(&filelist);
    dq_addlast(&down_list->node, &filelist);
    if(g_down_pid  < 0)
        thread_init();
    return;
}

