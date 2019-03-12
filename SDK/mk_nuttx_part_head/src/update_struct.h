#ifndef __UPDATE_STRUCT_H__
#define __UPDATE_STRUCT_H__

#define UPDATE_PART_NULL    0
#define UPDATE_PART_KERNEL  1
#define UPDATE_PART_ROOTFS  2

#define STAT_OK             0
#define STAT_IN_SEC_SYS     1
#define STAT_IN_BACKUP      2

#define UPDATE_FD_1 1
#define UPDATE_FD_2 2

struct part_head_info {
	int magic;
	int len;
	int checksum;
	//above are legacy
	int update_start_addr;
	int update_length;
	char sys_version[32];
	char product_version[32];
	char recv_0[32];
	int arch_version;
	//for later use
	int recv_1;
	int recv_2;
	int recv_3;
};

struct boot_data_info {
	int magic;
	int count;
	int checksum;
	int backup_len;	
	//following are used for linux
	char last_boot_method;
	char kernel_stat;
	char rootfs_stat;
	char resv;
	//above are legacy
	int update_stat;
	int backup_addr;
	int rootfs_addr;
};

#endif
