/* Copyright (c) 2017 - 2018, Realtek
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *      list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *   3. Neither the name of Realtek nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef RTW_RAAL_CONFIG_H__
#define RTW_RAAL_CONFIG_H__

#ifdef RTW_802154_PROJECT_CONFIG
#include RTW_802154_PROJECT_CONFIG
#endif

#include <realtek.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rtw_raal_config RAAL configuration
 * @{
 * @ingroup rtw_802154
 * @brief Configuration of Radio Arbiter Abstraction Layer.
 */

/**
 * @def RTW_RAAL_MAX_CLEAN_UP_TIME_US
 *
 * The maximum time in which the radio driver must do any clean-up actions on the RADIO peripheral
 * and stop using it.
 *
 */
#ifndef RTW_RAAL_MAX_CLEAN_UP_TIME_US
#define RTW_RAAL_MAX_CLEAN_UP_TIME_US 91
#endif

/**
 *@}
 **/

#ifdef __cplusplus
}
#endif

#endif // RTW_RAAL_CONFIG_H__
