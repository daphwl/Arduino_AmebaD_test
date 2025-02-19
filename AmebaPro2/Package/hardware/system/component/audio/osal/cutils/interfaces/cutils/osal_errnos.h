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

#ifndef AMEBA_CUTILS_OSAL_ERRNOS_H
#define AMEBA_CUTILS_OSAL_ERRNOS_H

#include <sys/types.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	OSAL_OK                      = 0,    // Everything's swell.


	OSAL_ERR_UNKNOWN_ERROR       = (-2147483647 - 1), // INT32_MIN value

	OSAL_ERR_NO_MEMORY           = -ENOMEM,
	OSAL_ERR_INVALID_OPERATION   = -ENOSYS,
	OSAL_ERR_INVALID_PARAM       = -EINVAL,
	OSAL_ERR_NAMERR_NOT_FOUND    = -ENOENT,
	OSAL_ERR_PERMISSION_DENIED   = -EPERM,
	OSAL_ERR_NO_INIT             = -ENODEV,
	OSAL_ERR_ALREADY_EXISTS      = -EEXIST,
	OSAL_ERR_DEAD_OBJECT         = -EPIPE,
	OSAL_ERR_BAD_INDEX           = -EOVERFLOW,
	OSAL_ERR_NOT_ENOUGH_DATA     = -ENODATA,
	OSAL_ERR_WOULD_BLOCK         = -EWOULDBLOCK,
	OSAL_ERR_TIMED_OUT           = -ETIMEDOUT,
	OSAL_ERR_UNKNOWN_TRANSACTION = -EBADMSG,

	OSAL_ERR_FAILURE             = (OSAL_ERR_UNKNOWN_ERROR + 1),
	OSAL_ERR_NOT_SUPPORT         = (OSAL_ERR_UNKNOWN_ERROR + 2),
};

#ifdef __cplusplus
}
#endif

#endif // AMEBA_CUTILS_OSAL_ERRNOS_H