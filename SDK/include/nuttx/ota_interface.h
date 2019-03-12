/************************************************************************************
 *include/nuttx/ota_interface.h
 *
 * Copyright (C) 2015 The YunOS Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/

#ifndef _OTA_INTERFACE_H_
#define _OTA_INTERFACE_H_

#include <stdint.h>

#define OTA_UPDATE_WRITE_FIN  1
#define OTA_UPDATE_SUCESS 2
#define OTA_UPDATE_FIALED 3

#define ENC_IMG_FLAG 3

typedef struct _image_desc 
 {
    int32_t  imgsz; 
    int8_t   imgname[8];
    int32_t  staticaddr;
    int32_t  loadaddr;
    uint8_t  enc;
 }image_desc_s;

/****************************************************************************
* Name: get_system_version
*
* Description:
*   Get current system version
*
* Input parameters:
*   void
*
* Returned Value:
*   Return version char
*
* Assumptions:
*
*****************************************************************************/
char* get_system_version(void);

/****************************************************************************
* Name: get_product_type
*
* Description:
*   Get current product type 
*
* Input parameters:
*   void
*
* Returned Value:
*   Return typr char
*
* Assumptions:
*
*****************************************************************************/
char* get_product_type(void);

/****************************************************************************
* Name: get_product_internal_type
*
* Description:
*   Get current product type
*
* Input parameters:
*   void
*
* Returned Value:
*   Return type char
*
* Assumptions:
*
*****************************************************************************/
char* get_product_internal_type(void);

/****************************************************************************
* Name: get_manifest_addr
*
* Description:
*   Get manifest address in flash
*
* Input parameters:
*   void
*
* Returned Value:
*   Return flash address
*
* Assumptions:
*
*****************************************************************************/
uint32_t get_manifest_addr(void);


/****************************************************************************
* Name: get_image_addr
*
* Description:
*   Get current image address for update
*
* Input parameters:
*   void
*
* Returned Value:
*   Return the address in flash
*
* Assumptions:
*
*****************************************************************************/
uint32_t get_image_addr(void);

/****************************************************************************
* Name: get_image_desc
*
* Description:
*   Get image descriptor by index
*
* Input parameters:
*   idx        the image index
*   img_desc   the output descriptor
* Returned Value:
*   Return success or fail
*
* Assumptions:
*
*****************************************************************************/
int32_t get_image_desc(int32_t idx,  int32_t partition, image_desc_s *img_desc);


/****************************************************************************
* Name: get_image_max_size
*
* Description:
*   Get the max size of a image
*
* Input parameters:
*   void
*
* Returned Value:
*   Return the max size of image
*
* Assumptions:
*
*****************************************************************************/
uint32_t get_image_max_size();

/****************************************************************************
* Name: flash_page_program
*
* Description:
*   Write buffer to flash
*
* Input parameters:
*   start_addr - flash adrress
*   buf_len    - buffer length
*   buf        - buffer
*
* Returned Value:
*   Zero on success; a negated errno value on failure
*
* Assumptions:
*
*****************************************************************************/
int32_t flash_page_program(uint32_t start_addr, int32_t buf_len, uint8_t *buf);

/****************************************************************************
* Name: switch_bootup_partition
*
* Description:
*   switch between primary partition and update partition
*
* Input parameters:
*   void 
*
* Returned Value:
*   Zero on success; a negated errno value on failure
*
* Assumptions:
*
*****************************************************************************/
int32_t switch_bootup_partition(void);

/****************************************************************************
* Name: set_update_finished_flags
*
* Description:
*   Write flags to flash, when finished update data write 
*
* Input parameters:
*   void 
*
* Returned Value:
*   Zero on success; a negated errno value on failure
*
* Assumptions:
*
*****************************************************************************/
int32_t set_update_finished_flags(void);


/****************************************************************************
* Name: get_update_result
*
* Description:
*   get update result from flash
*
* Input parameters:
*   void 
*
* Returned Value:
*   OTA_UPDATE_WRITE_FIN  just write udpate image to flash
*   OTA_UPDATE_SUCESS     after reboot,load the new system, update success
*   OTA_UPDATE_FIALED     update failed
* Assumptions:
*
*****************************************************************************/
int16_t get_update_result(void);

/****************************************************************************
* Name: get_partition_state
*
* Description:
*   get validity of primary and update partition
*
* Input parameters:
*   void 
*
* Returned Value:
*   the first bit in return stand for primary partition
*   the second bit in return stand for update partition
*   when the bit is set to 1 it means the partition is not vaild
*   when the bit is clear to 0 it means the partition is vaild
*   other situations are ignored
* Assumptions:
*
*****************************************************************************/
int16_t get_partition_state(void);


/****************************************************************************
* Name: read_image_contex
*
* Description:
*   read the contex of a image
*
* Input parameters:
*   img_desc        - image description
*   read_offset     - read offset
*   read_buf        - read buffer
*   read_buf_size       - buffer size
*
* Returned Value:
*   Zero on success; a negated errno value on failure
*
*****************************************************************************/
int32_t read_image_contex( image_desc_s * img_desc, uint32_t read_offset, uint8_t * read_buf, uint32_t  read_buf_size);

/****************************************************************************
* Name: get_primary_version
*
* Description:
* get the system version of primary path
*
* Input parameters:
*   buf  input buf
*   len  input buf length
* Returned Value:
* Assumptions:
*
*****************************************************************************/
int32_t get_primary_version(char *buf, int32_t len);

/****************************************************************************
* Name: get_update_version
*
* Description:
* get the system version of update path
*
* Input parameters:
*   buf  input buf
*   len  input buf length
* Returned Value:
* Assumptions:
*
*****************************************************************************/
int32_t get_update_version(char *buf, int32_t len);

/****************************************************************************
* Name: update_system_version
*
* Description:
*   update system version(primary path and update path) in system config
*
* Input parameters:
*   void 
*
* Returned Value:
* 0 when the version does not change
* 1 when the version is updated
* Assumptions:
*
*****************************************************************************/
int update_system_version(void);


//just from debug
void show_config_info(void);
#endif
