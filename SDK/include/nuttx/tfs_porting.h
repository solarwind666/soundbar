/****************************************************************************
* include/nuttx/tfs_porting.h
*
* Copyright (C) 2016 The YunOS Open Source Project
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
****************************************************************************/

#ifndef __TFS_PORTING_H__
#define __TFS_PORTING_H__
#include "stdint.h"

/* functions declare */

/****************************************************************************
* Name: DeviceOpen
*
* Description:
*   open the corresponding device
*
* Input Parameters:
*   handle - distinguish device
*
* Returned Values:
*   OK or NO-ZERO
*
****************************************************************************/

int DeviceOpen(void **handle);

/****************************************************************************
* Name: DeviceTransmit
*
* Description:
*   Device transmit operation
*
* Input Parameters:
*   handle - distinguish device
*   txbuf - the address store the send data
*   txlen - send data length
*   rxbuf - the address sore the recieve data
*   rxlen - recieve data length
*
* Returned Values:
*   OK or NO-ZERO
*
****************************************************************************/

int DeviceTransmit(void *handle, uint8_t *txbuf, int txlen, uint8_t *rxbuf, int *rxlen);

/****************************************************************************
* Name: DeviceClose
*
* Description:
*   close the corresponding device
*
* Input Parameters:
*   handle - distinguish device
*
* Returned Values:
*   OK or NO-ZERO
*
****************************************************************************/

int DeviceClose(void *handle);

#endif
