/****************************************************************************
 * /arch/cskyv1/src/cskyv1/csky_coredump.h
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


#ifndef CSKY_COREDUMP_H
#define CSKY_COREDUMP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <stdint.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/
extern void do_coredump(uint32_t *regs);
#endif
