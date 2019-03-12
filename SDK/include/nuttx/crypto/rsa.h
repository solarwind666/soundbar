
/***********************************************************************************
 * include/nuttx/crypto/rsa.h
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

#ifndef _RSA_H_
#define _RSA_H_
 
#ifdef CONFIG_CRYPTO_HW_RSA
#define RSA_PKCS1_OAEP_PADDING  0
#define RSA_PKCS1_PADDING   1
#define RSA_NO_PADDING  2

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/


 /************************************************************************** 
 * Function: rsa_decrypt
 *
 * Description:
 *     this is RSA decrypt interface, set private key to drm rsa ,and get the decrypted message
 *
 * Parameters:  
 *     pem_prikey:  private key in pem format
 *     output: buffer of decrypted message
 *     max_olen: max output length
 *     b64input:  input message
 *     padding:   padding mode,  RSA_PKCS1_OAEP_PADDING or RSA_NO_PADDING
 * Returned Value:
 *     output length on success
 *     -1: failed
 *
 * Assumptions:
 *  
 **************************************************************************/
int rsa_decrypt( const char *pem_key, unsigned char *output, int max_olen, 
                                                const char *b64input, int padding);  

#endif

#endif
