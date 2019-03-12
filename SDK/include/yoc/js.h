/*
 * Copyright (C) 2016 YunOS Project. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file yoc/js.h
 * @brief YOC JavaScript APIs
 * @version since 5.6.1
 */

#ifndef YOC_JS_API_H
#define YOC_JS_API_H

#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup yoc_js JavaScript APIs
 *  @{
 */

/**
 * @brief run a JavaScript code
 * @param code_buf JavaScript code buffer
 * @param code_len JavaScript code length
 * @retval ==0 success
 * @retval !=0 failure
 */
int yoc_js_eval(const char *code_buf, int code_len);

/** @} */ //end of Framework APIs

#ifdef __cplusplus
}
#endif

#endif /* YOC_JS_API_H */

