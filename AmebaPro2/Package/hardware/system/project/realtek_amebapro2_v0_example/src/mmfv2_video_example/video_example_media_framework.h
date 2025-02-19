#ifndef MMF2_VIDEO_EXAMPLE_H
#define MMF2_VIDEO_EXAMPLE_H

#include "platform_opts.h"
#include "sensor.h"

#define USR_CMD_RTSP_PAUSE			    (u32)0x1
#define USR_CMD_RTSP1_PAUSE 			(u32)(0x1 << 1)
#define USR_CMD_RTSP2_PAUSE 			(u32)(0x1 << 2)
#define USR_CMD_RTSP3_PAUSE 			(u32)(0x1 << 3)
#define USR_CMD_AUDIO_PAUSE 			(u32)(0x1 << 4)
#define USR_CMD_VIDEO_PAUSE 			(u32)(0x1 << 8)
#define USR_CMD_VIDEO1_PAUSE 			(u32)(0x1 << 9)
#define USR_CMD_RECORD_PAUSE            (u32)(0x1 << 12)
#define USR_CMD_RTP_PAUSE               (u32)(0x1 << 16)
#define USR_CMD_MBNSSD_PAUSE            (u32)(0x1 << 20)
#define USR_CMD_FRC_PAUSE               (u32)(0x1 << 21)
#define USR_CMD_VIPNN_PAUSE             (u32)(0x1 << 22)
#define USR_CMD_EXAMPLE_DEINIT		    (u32)(0x1 << 30)

void video_example_media_framework(void);

void mmf2_video_example_v1_init(void);

void mmf2_video_example_v2_init(void);

void mmf2_video_example_v3_init(void);

void mmf2_video_example_v1_shapshot_init(void);

void mmf2_video_example_simo_init(void);

void mmf2_video_example_av_init(void);

void mmf2_video_example_av2_init(void);

void mmf2_video_example_av21_init(void);

void mmf2_video_example_av_mp4_init(void);

void mmf2_video_example_av_rtsp_mp4_init(void);

void mmf2_video_example_joint_test_init(void);

void mmf2_video_example_joint_test_rtsp_mp4_init(void);

void mmf2_video_example_2way_audio_pcmu_doorbell_init(void);

void mmf2_video_example_2way_audio_pcmu_init(void);

void mmf2_video_example_array_rtsp_init(void);

void mmf2_video_example_v1_param_change_init(void);

void mmf2_video_example_av_mp4_httpfs_init(void);

void mmf2_video_example_v4_rgb_init(void);

void mmf2_video_example_v1_reset_init(void);

void mmf2_video_example_joint_test_vipnn_rtsp_mp4_init(void);

void mmf2_video_example_joint_test_rtsp_mp4_init_fcs(void);

#endif /* MMF2_VIDEO_EXAMPLE_H */