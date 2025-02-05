/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_CUTILS_OSAL_MUTEX_H
#define AMEBA_CUTILS_OSAL_MUTEX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct OsalMutex {
	void *mutex;
} OsalMutex;

#define OSAL_DECLARE_MUTEX(mutex) OsalMutex mutex

int32_t OsalMutexInit(OsalMutex *mutex);
int32_t OsalMutexDestroy(OsalMutex *mutex);
int32_t OsalMutexLock(OsalMutex *mutex);
int32_t OsalMutexTrylock(OsalMutex *mutex);
int32_t OsalMutexUnlock(OsalMutex *mutex);


#ifdef __cplusplus
}
#endif

#endif // AMEBA_CUTILS_OSAL_MUTEX_H