#ifndef _MANIFEST_H_
#define _MANIFEST_H_

#define    IMAGE_NUM       3

typedef struct _image_desc_t
  { 
    unsigned int     idx;
    unsigned int     imgsz;
    unsigned int     staticaddr;
    unsigned int     loadaddr;
    unsigned int     checksum;
    char    enc;
    char    copy;
    char    imgname[8];
    char    sig[128];
  }image_desc_t;

typedef struct _manifest_t
  {
    unsigned int     magic;
    unsigned int     version;
    unsigned int     boot_idx;
    unsigned int     imgnum;
    unsigned int     digsch;
    unsigned int     sigsch;
    unsigned int     size;
    image_desc_t   images[IMAGE_NUM];
  } manifest_t;

#endif
