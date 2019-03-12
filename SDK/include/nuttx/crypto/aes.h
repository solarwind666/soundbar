/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/************************************************************************************
 * include/nuttx/crypto/aes.h
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

#ifndef __INCLUDE_NUTTX_CRYPTO_AES_H
#define __INCLUDE_NUTTX_CRYPTO_AES_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define AES128_KEY_SIZE    16

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef  __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: aes_encrypt
 *
 * Description:
 *   AES128 encryption:  Given AES128 key and 16 bytes plain text, cipher
 *   text of 16 bytes is computed. The AES implementation is in mode ECB
 *   (Electronic Code Book).
 *
 * Input Parameters:
 *  key   AES128 key of size 16 bytes
 *  state 16 bytes of plain text and cipher text
 *
 * Returned Value
 *   None
 *
 ****************************************************************************/

void aes_encrypt(FAR uint8_t *state, FAR const uint8_t *key);

/****************************************************************************
 * Name: aes_decrypt
 *
 * Description:
 *   AES128 decryption: Given AES128 key and 16 bytes cipher text, plain
 *   text of 16 bytes is computed The AES implementation is in mode ECB
 *   (Electronic Code Book).
 *
 * Input Parameters:
 *  key   AES128 key of size 16 bytes
 *  state 16 bytes of plain text and cipher text
 *
 * Returned Value
 *   None
 *
 ****************************************************************************/

void aes_decrypt(FAR uint8_t *state, FAR const uint8_t *key);

/***************************************************************************
 * Function: aes_encrypt_cbc
 *
 * Description:
 *    CBC mode aes encrypt
 *
 * Parameters:
 *    key[in]     the input aes key
 *    iv[in]      the input initial vector
 *    input[in]   the input aes data
 *    output[out] the output aes data
 * Returned Value:
 *    succeed or errorno
 * Assumptions:
 *
 **************************************************************************/
int32_t aes_encrypt_cbc(const uint8_t *key,
                        const uint8_t *iv,
                        int32_t input_len,
                        const uint8_t *input,
                        uint8_t *output);


/***************************************************************************
 * Function: aes_decrypt_cbc
 *
 * Description:
 *    CBC mode aes decrypt
 *
 * Parameters:
 *    key[in]     the input aes key
 *    iv[in]      the input initial vector
 *    input[in]   the input aes data
 *    output[out] the output aes data
 * Returned Value:
 *    succeed or errorno
 * Assumptions: 
 *
 **************************************************************************/
int32_t aes_decrypt_cbc(const uint8_t *key,
                           const uint8_t *iv,
                           int32_t input_len,
                           const uint8_t *input,
                           uint8_t *output);

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCLUDE_NUTTX_CRYPTO_AES_H */
