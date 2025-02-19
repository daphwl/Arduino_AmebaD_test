#ifndef _MODULE_VIDEO_H
#define _MODULE_VIDEO_H

#include <stdint.h>
#include <osdep_service.h>
#include "mmf2_module.h"
#include "video_api.h"

#define CMD_VIDEO_SET_PARAMS     	MM_MODULE_CMD(0x00)  // set parameter
#define CMD_VIDEO_GET_PARAMS     	MM_MODULE_CMD(0x01)  // get parameter
#define CMD_VIDEO_SET_HEIGHT		MM_MODULE_CMD(0x02)
#define CMD_VIDEO_SET_WIDTH			MM_MODULE_CMD(0x03)
#define CMD_VIDEO_BITRATE			MM_MODULE_CMD(0x04)

#define CMD_VIDEO_GOP				MM_MODULE_CMD(0x06)
#define CMD_VIDEO_MEMORY_SIZE		MM_MODULE_CMD(0x07)
#define CMD_VIDEO_BLOCK_SIZE		MM_MODULE_CMD(0x08)
#define CMD_VIDEO_MAX_FRAME_SIZE	MM_MODULE_CMD(0x09)
#define CMD_VIDEO_RCMODE			MM_MODULE_CMD(0x0a)
#define CMD_VIDEO_SET_RCPARAM		MM_MODULE_CMD(0x0b)
#define CMD_VIDEO_GET_RCPARAM		MM_MODULE_CMD(0x0c)
#define CMD_VIDEO_INIT_MEM_POOL		MM_MODULE_CMD(0x0d)
#define CMD_VIDEO_FORCE_IFRAME		MM_MODULE_CMD(0x0e)
#define CMD_VIDEO_SET_RCADVPARAM	MM_MODULE_CMD(0x10)
#define CMD_VIDEO_GET_RCADVPARAM	MM_MODULE_CMD(0x11)
#define CMD_VIDEO_SET_ROIPARM		MM_MODULE_CMD(0x12)
#define CMD_VIDEO_SET_ROI			MM_MODULE_CMD(0x13)
#define CMD_VIDEO_SET_QPCHROMA_OFFSET    MM_MODULE_CMD(0x14)
#define CMD_VIDEO_SET_FORCE_DROP_FRAME   MM_MODULE_CMD(0x15)


#define CMD_VIDEO_STREAMID		    MM_MODULE_CMD(0x16)
#define CMD_VIDEO_FORMAT			MM_MODULE_CMD(0x17)
#define CMD_VIDEO_DUMP_STATE		MM_MODULE_CMD(0x18)
#define CMD_VIDEO_BPS               MM_MODULE_CMD(0x19)
#define CMD_VIDEO_SNAPSHOT          MM_MODULE_CMD(0x1a)
#define CMD_VIDEO_SNAPSHOT_CB       MM_MODULE_CMD(0x1b)
#define CMD_VIDEO_YUV               MM_MODULE_CMD(0x1c)
#define CMD_ISP_SET_RAWFMT          MM_MODULE_CMD(0x1d)
#define CMD_VIDEO_PRINT_INFO        MM_MODULE_CMD(0x1e)



#define CMD_VIDEO_APPLY				MM_MODULE_CMD(0x20)  // apply setting
#define CMD_VIDEO_UPDATE			MM_MODULE_CMD(0x21)  // update new setting
#define CMD_VIDEO_STREAM_STOP		MM_MODULE_CMD(0x23)  // stop stream

#define CMD_VIDEO_SET_VOE_HEAP      MM_MODULE_CMD(0x24)

#define CMD_SNAPSHOT_ENCODE_CB		MM_MODULE_CMD(0x30)


#define CMD_VIDEO_MD_SET_ROI		MM_MODULE_CMD(0x31)
#define CMD_VIDEO_MD_SET_SENSITIVITY	MM_MODULE_CMD(0x32)
#define CMD_VIDEO_MD_START			MM_MODULE_CMD(0x33)
#define CMD_VIDEO_MD_STOP			MM_MODULE_CMD(0x34)

typedef struct video_ctx_s {
	void *parent;

	hal_video_adapter_t *v_adp;
	void *mem_pool;

	video_params_t params;
	int (*snapshot_cb)(uint32_t, uint32_t);
	void (*change_parm_cb)(void *);
	video_state_t state;

} video_ctx_t;

extern mm_module_t video_module;


int video_voe_presetting(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_shapshot,
						 int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_shapshot,
						 int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_shapshot,
						 int v4_enable, int v4_w, int v4_h);

void video_voe_release(void);
void video_set_sensor_id(int SensorName);

#endif