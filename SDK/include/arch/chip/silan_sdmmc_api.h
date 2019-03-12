#ifndef _SDMMC_API_H_
#define _SDMMC_API_H_

typedef struct sdmmc_rw_desc {
    unsigned int addr ;
    unsigned int len;
    unsigned char *buf;
} t_sdmmc_rw_desc;

typedef enum {
    VFAT_READ = 0,
    VFAT_WRITE,
} VFAT_COMMAND;

typedef struct sdmmc_ctrl_desc {
    VFAT_COMMAND command;
    unsigned char *shortName;
    unsigned char *buf;
    unsigned int size;
} t_sdmmc_ctrl_desc;

signed int  silan_emmc_boot_access_config(void);
signed int  silan_emmc_boot_out(void);
#endif

