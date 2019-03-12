/****************************************************************************
 * arch/csky/src/cskyv1/cache.h
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
 ****************************************************************************/

#ifndef __ARCH_CSKY_SRC_CSKYV2_L_CACHE_H
#define __ARCH_CSKY_SRC_CSKYV2_L_CACHE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Defintiions
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/

#define yunos_csp_flush_icache_range(start, end)  drv_dcache_invalid_range(start, end-start)

#define flush_dcache_all                  drv_dcache_clean
#define flush_dcache_range(start, end)    drv_dcache_clean_range(start, end-start)
#define invalid_dcache_all                drv_dcache_invalid
#define invalid_dcache_range(start, end)  drv_dcache_invalid_range(start, end-start)

#endif /* __ARCH_CSKY_SRC_CSKYV2_L_CACHE_H */

