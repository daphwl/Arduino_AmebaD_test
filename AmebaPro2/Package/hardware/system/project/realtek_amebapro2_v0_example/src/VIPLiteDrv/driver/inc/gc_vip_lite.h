/******************************************************************************\
|* Copyright (c) 2017-2021 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _GC_VIP_LITE_H
#define _GC_VIP_LITE_H

#include <gc_vip_common.h>
#include <gc_vip_nbg_format.h>
#include <vip_lite.h>

typedef enum _gcvip_obj_type {
	GCVIP_OBJ_NONE          = 0x00,
	GCVIP_OBJ_NETWORK       = 0x01,
	GCVIP_OBJ_BUFFER        = 0x02,
	GCVIP_OBJ_IMAGE         = 0x03,
	GCVIP_OBJ_NODE          = 0x04,
	GCVIP_OBJ_MAX,
} gcvip_obj_type_e;

typedef enum _gcvip_buffer_allocate {
	GCVIP_BUFFER_ALLOCATE_NONE                = 0,
	GCVIP_BUFFER_ALLOCATE_FROM_INTERNAL       = 1,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_MEMORY    = 2,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_PHYSICAL  = 3,
	GCVIP_BUFFER_ALLOCATE_MAX                 = 4,
} gcvip_buffer_allocate_e;

typedef enum _gcvip_cmd_type {
	GCVIP_OPERATION_TYPE_NONE       = 0,
	GCVIP_OPERATION_TYPE_SH         = 1,
	GCVIP_OPERATION_TYPE_NN         = 2,
	GCVIP_OPERATION_TYPE_TP         = 3,
	GCVIP_OPERATION_TYPE_SW         = 4,
	GCVIP_OPERATION_TYPE_SC         = 5,
	GCVIP_OPERATION_TYPE_END        = 0xFFFE,
	GCVIP_OPERATION_TYPE_INIT       = 0xFFFF,
} gcvip_cmd_type_e;

typedef enum _gcvip_init_cmd_status {
	GCVIP_INIT_CMD_STATUS_NO         = 0,
	GCVIP_INIT_CMD_STATUS_DONE       = 1,
	GCVIP_INIT_CMD_STATUS_POWER_OFF  = 2,
} gcvip_init_cmd_status_e;

typedef struct _gcvip_object {
	gcvip_obj_type_e  type;
} gcvip_object_t;

/* video memory object that VIP hardware could access */
typedef struct _gcvip_videomemory_t {
	/*
	an anonymous handle to this video memory object.
	it can be parsed video memory maintiner.
	*/
	void                *handle;
	/* the virtual address of this video memory */
	vip_uint8_t         *logical;
	/* the physical address */
	vip_uint32_t        physical;
	/* the size of the video memory */
	vip_uint32_t        size;
} gcvip_videomemory_t;

typedef struct _gcvip_context {
	/* cid */
	vip_uint32_t        hw_target;
	vip_uint32_t        axi_sram_base;
	vip_uint32_t        axi_sram_size;
	vip_uint32_t        vip_sram_base;
	vip_uint32_t        vip_sram_size;

	volatile vip_int8_t  initialize;
	volatile vip_uint8_t init_status;

#if vpmdENABLE_CAPTURE
	void                *capture_file;
#endif

#if vpmdENABLE_MULTIPLE_TASK
	/* mutex for vip_init/vip_destroy */
	void                *initialize_mutex;
	void                *init_cmds_mutex;
#endif

	/* Initialize Config Data */
	gcvip_videomemory_t ICD;
	/* initialize PPU,NN,TP */
	gcvip_videomemory_t init_commands;
} gcvip_lite_context_t;

typedef struct _vip_buffer {
	gcvip_object_t      object;
	gcvip_videomemory_t memory;
	vip_uint32_t        allocated;
	vip_buffer_create_params_t param;
} vip_buffer_t;

typedef struct _gcvip_group_item {
	gcvip_object_t      object;
	vip_ptr             task;
} gcvip_group_item_t;

typedef struct _vip_group {
	gcvip_group_item_t    *tasks;
	vip_uint32_t           count;
	vip_uint32_t           max_task_num;
	vip_uint32_t           run_task_num;
#if vpmdENABLE_MULTIPLE_TASK
	void                  *mutex;
#endif
} vip_group_t;

#if vpmdENABLE_CAPTURE
typedef struct _gcvip_command_dump {
	vip_uint32_t cmd_type;
	vip_uint32_t size;
	vip_uint32_t offset;
	vip_uint32_t layer_id;
	vip_uint32_t uid;
	struct _gcvip_command_dump *next;
} gcvip_command_dump_t;
#endif

#if vpmdENABLE_USE_AGENT_TRIGGER
/* vip_input_output_info_t and vip_address_info_t should be defined into agent driver
*/

/*! \brief network's inputs/outputs address in command buffer. it only used by Agent driver.
 */
typedef struct _vip_input_output_info {
	/*!< the logical address of input/output in command buffer */
	void                *logical_in_cmd;
	/*!< the physical address of input/output in command buffer */
	vip_uint32_t        *physical_in_cmd;
	/*!< the offset for every slice */
	vip_uint32_t        *offset;
	/*!< the number of input/output slice */
	vip_uint32_t        slice_num;
	/*!< the physical address of input/output buffer */
	vip_uint32_t        physical;
} vip_input_output_info_t;

/*! \brief address infromation of network's buffers, it only used by Agent driver.
 */
typedef struct _vip_address_info {
	/*!< the logical address of wait-link buffer */
	void                *waitlink_logical;
	/*!< the physical address of wait-link buffer */
	vip_uint32_t        waitlink_physical;
	/*!< the size of wait-link buffer */
	vip_uint32_t        waitlink_size;

	/*!< the logical address of command buffer */
	void                *commandbuffer_logical;
	/*!< the physical address of command buffer */
	vip_uint32_t        commandbuffer_physical;
	/*!< the size of commands */
	vip_uint32_t        commandbuffer_size;

	/*!< network's input information */
	vip_input_output_info_t *input_info;
	/*!< the number of inputs */
	vip_uint32_t            input_num;

	/*!< network's output information */
	vip_input_output_info_t *output_info;
	/*!< the number of outputs */
	vip_uint32_t            output_num;
} vip_address_info_t;
#endif

#endif
