#ifndef _MODULE_KVS_WEBRTC_H
#define _MODULE_KVS_WEBRTC_H

#include "mmf2_module.h"

#define CMD_KVS_WEBRTC_SET_PARAMS       MM_MODULE_CMD(0x00)
#define CMD_KVS_WEBRTC_GET_PARAMS       MM_MODULE_CMD(0x01)
#define CMD_KVS_WEBRTC_SET_APPLY        MM_MODULE_CMD(0x02)
#define CMD_KVS_WEBRTC_STOP             MM_MODULE_CMD(0x03)

typedef struct kvsWebrtcMediaQueue_s {
	xQueueHandle VideoSendQueue;
	xQueueHandle AudioSendQueue;
	xQueueHandle AudioRecvQueue;

} kvsWebrtcMediaQueue_t;

extern kvsWebrtcMediaQueue_t *pkvsWebrtcMediaQ;

typedef struct kvs_webrtc_ctx_s {
	void *parent;
	TaskHandle_t    kvs_webrtc_module_main_task;
	TaskHandle_t    kvs_webrtc_module_audio_recv_task;

	bool mediaStop;

} kvs_webrtc_ctx_t;

extern mm_module_t kvs_webrtc_module;

#endif /* _MODULE_KVS_WEBRTC_H */