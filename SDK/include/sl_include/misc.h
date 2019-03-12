/************************************************************************************
 *arch/cskyv1/src/cskyv1/up_blocktask.c
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

#ifndef __INCLUDE_MISC_H__
#define __INCLUDE_MISC_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>
#include <pthread.h>

/****************************************************************************
 * Data structs
 ****************************************************************************/

/****************************************************************************
 * Functions
 ****************************************************************************/
/*
 * getcpuusage
 *    used to get task CPU usage, return a number which means percentage
 *
 * Input:
 *    pid -  task PID
 *
 * Return:
 *    a number which means percentage
 */
int32_t get_cpu_usage(pid_t pid);

#endif
