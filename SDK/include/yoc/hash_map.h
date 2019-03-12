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
 */

#ifndef YOC_HASH_MAP_H
#define YOC_HASH_MAP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    void *handle;
} hash_map_t;

hash_map_t hash_map_create(size_t capacity);

int hash_map_put(hash_map_t map, const char *key, void *value);

int hash_map_get(hash_map_t map, const char *key, void **value);

void *hash_map_remove(hash_map_t map, const char *key);

size_t hash_map_size(hash_map_t map);

void hash_map_destroy(hash_map_t map, void (*free_cb)(void *value));

int hash_map_foreach(
        hash_map_t map,
        int (*foreach_cb)(const char *key, void *value, void *private_data),
        void *private_data);

#ifdef __cplusplus
}
#endif

#endif /* YOC_HASH_MAP_H */

