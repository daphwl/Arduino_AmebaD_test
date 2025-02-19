/*
 * ISO Media common code
 * copyright (c) 2001 Fabrice Bellard
 * copyright (c) 2002 Francois Revol <revol@free.fr>
 * copyright (c) 2006 Baptiste Coudurier <baptiste.coudurier@free.fr>
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVFORMAT_ISOM_H
#define AVFORMAT_ISOM_H

#include <stddef.h>
#include <stdint.h>

#include "libavutil/spherical.h"
#include "libavutil/stereo3d.h"

#include "avio.h"
#include "internal.h"
#include "dv.h"

/* isom.c */
extern const AVCodecTag ff_mp4_obj_type[];
extern const AVCodecTag ff_codec_movvideo_tags[];
extern const AVCodecTag ff_codec_movaudio_tags[];
extern const AVCodecTag ff_codec_movsubtitle_tags[];

int ff_mov_iso639_to_lang(const char lang[4], int mp4);
int ff_mov_lang_to_iso639(unsigned code, char to[4]);

/* the QuickTime file format is quite convoluted...
 * it has lots of index tables, each indexing something in another one...
 * Here we just use what is needed to read the chunks
 */

typedef struct MOVStts {
    int count;
    int duration;
} MOVStts;

typedef struct MOVStsc {
    int first;
    int count;
    int id;
} MOVStsc;

typedef struct MOVDref {
    uint32_t type;
    char *path;
    char *dir;
    char volume[28];
    char filename[64];
    int16_t nlvl_to, nlvl_from;
} MOVDref;

typedef struct MOVAtom {
    uint32_t type;
    int64_t size; /* total size (excluding the size and type fields) */
} MOVAtom;

struct MOVParseTableEntry;

typedef struct MOVFragment {
    unsigned track_id;
    uint64_t base_data_offset;
    uint64_t moof_offset;
    uint64_t implicit_offset;
    unsigned stsd_id;
    unsigned duration;
    unsigned size;
    unsigned flags;
} MOVFragment;

typedef struct MOVTrackExt {
    unsigned track_id;
    unsigned stsd_id;
    unsigned duration;
    unsigned size;
    unsigned flags;
} MOVTrackExt;

typedef struct MOVSbgp {
    unsigned int count;
    unsigned int index;
} MOVSbgp;

typedef struct MOVStreamContext {
    AVIOContext *pb;
    int ffindex;          ///< AVStream index
    int next_chunk;
    unsigned int chunk_count;
    int64_t *chunk_offsets;
    unsigned int stts_count;
    MOVStts *stts_data;
    unsigned int ctts_count;
    MOVStts *ctts_data;
    unsigned int stsc_count;
    MOVStsc *stsc_data;
    unsigned int stsc_index;
    int stsc_sample;
    unsigned int stps_count;
    unsigned *stps_data;  ///< partial sync sample for mpeg-2 open gop
    int ctts_index;
    int ctts_sample;
    unsigned int sample_size;
    unsigned int sample_count;
#if !(defined(CONFIG_PLATFORM_8195A)||defined(CONFIG_PLATFORM_8721D))
    int *sample_sizes;
#else
    int16_t *sample_sizes;
#endif
    int keyframe_absent;
    unsigned int keyframe_count;
    int *keyframes;
    int time_scale;
    int64_t time_offset;  ///< time offset of the first edit list entry
    int current_sample;
    unsigned int bytes_per_frame;
    unsigned int samples_per_frame;
    int dv_audio_container;
    int pseudo_stream_id; ///< -1 means demux all ids
    int16_t audio_cid;    ///< stsd audio compression id
    unsigned drefs_count;
    MOVDref *drefs;
    int dref_id;
    int width;            ///< tkhd width
    int height;           ///< tkhd height
    int dts_shift;        ///< dts shift when ctts is negative
    uint32_t palette[256];
    int has_palette;
    int64_t data_size;
    int64_t track_end;    ///< used for dts generation in fragmented movie files
    unsigned int rap_group_count;
    MOVSbgp *rap_group;

    /** extradata array (and size) for multiple stsd */
    uint8_t **extradata;
    int *extradata_size;
    int last_stsd_index;
    int stsd_count;

    int32_t *display_matrix;
    AVStereo3D *stereo3d;
    AVSphericalMapping *spherical;
    size_t spherical_size;
#if defined(CONFIG_PLATFORM_8195A) || defined(CONFIG_PLATFORM_8721D)
    int64_t chunk0_offset;
    int64_t current_pos;
#endif
} MOVStreamContext;

typedef struct MOVContext {
    const AVClass *class; ///< class for private options
    AVFormatContext *fc;
    int time_scale;
    int64_t duration;     ///< duration of the longest track
    int found_moov;       ///< 'moov' atom has been found
    int found_mdat;       ///< 'mdat' atom has been found
    DVDemuxContext *dv_demux;
    AVFormatContext *dv_fctx;
    int isom;             ///< 1 if file is ISO Media (mp4/3gp)
    MOVFragment fragment; ///< current fragment in moof atom
    MOVTrackExt *trex_data;
    unsigned trex_count;
    int itunes_metadata;  ///< metadata are itunes style
    int chapter_track;
    int seek_individually;
    int64_t next_root_atom; ///< offset of the next root atom
    int export_all;
    int export_xmp;
    int enable_drefs;

    int32_t movie_display_matrix[3][3]; ///< display matrix from mvhd
} MOVContext;

int ff_mp4_read_descr_len(AVIOContext *pb);
int ff_mp4_read_descr(AVFormatContext *fc, AVIOContext *pb, int *tag);
int ff_mp4_read_dec_config_descr(AVFormatContext *fc, AVStream *st, AVIOContext *pb);
void ff_mp4_parse_es_descr(AVIOContext *pb, int *es_id);

#define MP4ODescrTag                    0x01
#define MP4IODescrTag                   0x02
#define MP4ESDescrTag                   0x03
#define MP4DecConfigDescrTag            0x04
#define MP4DecSpecificDescrTag          0x05
#define MP4SLDescrTag                   0x06

#define MOV_TFHD_BASE_DATA_OFFSET       0x01
#define MOV_TFHD_STSD_ID                0x02
#define MOV_TFHD_DEFAULT_DURATION       0x08
#define MOV_TFHD_DEFAULT_SIZE           0x10
#define MOV_TFHD_DEFAULT_FLAGS          0x20
#define MOV_TFHD_DURATION_IS_EMPTY  0x010000
#define MOV_TFHD_DEFAULT_BASE_IS_MOOF 0x020000

#define MOV_TRUN_DATA_OFFSET            0x01
#define MOV_TRUN_FIRST_SAMPLE_FLAGS     0x04
#define MOV_TRUN_SAMPLE_DURATION       0x100
#define MOV_TRUN_SAMPLE_SIZE           0x200
#define MOV_TRUN_SAMPLE_FLAGS          0x400
#define MOV_TRUN_SAMPLE_CTS            0x800

#define MOV_FRAG_SAMPLE_FLAG_DEGRADATION_PRIORITY_MASK 0x0000ffff
#define MOV_FRAG_SAMPLE_FLAG_IS_NON_SYNC               0x00010000
#define MOV_FRAG_SAMPLE_FLAG_PADDING_MASK              0x000e0000
#define MOV_FRAG_SAMPLE_FLAG_REDUNDANCY_MASK           0x00300000
#define MOV_FRAG_SAMPLE_FLAG_DEPENDED_MASK             0x00c00000
#define MOV_FRAG_SAMPLE_FLAG_DEPENDS_MASK              0x03000000

#define MOV_FRAG_SAMPLE_FLAG_DEPENDS_NO                0x02000000
#define MOV_FRAG_SAMPLE_FLAG_DEPENDS_YES               0x01000000

#define MOV_TKHD_FLAG_ENABLED       0x0001
#define MOV_TKHD_FLAG_IN_MOVIE      0x0002
#define MOV_TKHD_FLAG_IN_PREVIEW    0x0004
#define MOV_TKHD_FLAG_IN_POSTER     0x0008

#define TAG_IS_AVCI(tag)                    \
    ((tag) == MKTAG('a', 'i', '5', 'p') ||  \
     (tag) == MKTAG('a', 'i', '5', 'q') ||  \
     (tag) == MKTAG('a', 'i', '5', '2') ||  \
     (tag) == MKTAG('a', 'i', '5', '3') ||  \
     (tag) == MKTAG('a', 'i', '5', '5') ||  \
     (tag) == MKTAG('a', 'i', '5', '6') ||  \
     (tag) == MKTAG('a', 'i', '1', 'p') ||  \
     (tag) == MKTAG('a', 'i', '1', 'q') ||  \
     (tag) == MKTAG('a', 'i', '1', '2') ||  \
     (tag) == MKTAG('a', 'i', '1', '3') ||  \
     (tag) == MKTAG('a', 'i', '1', '5') ||  \
     (tag) == MKTAG('a', 'i', '1', '6') ||  \
     (tag) == MKTAG('A', 'V', 'i', 'n'))


int ff_mov_read_esds(AVFormatContext *fc, AVIOContext *pb);

int ff_mov_read_stsd_entries(MOVContext *c, AVIOContext *pb, int entries);

/**
 * Compute codec id for 'lpcm' tag.
 * See CoreAudioTypes and AudioStreamBasicDescription at Apple.
 */
static inline enum AVCodecID ff_mov_get_lpcm_codec_id(int bps, int flags)
{
    /* lpcm flags:
     * 0x1 = float
     * 0x2 = big-endian
     * 0x4 = signed
     */
    return ff_get_pcm_codec_id(bps, flags & 1, flags & 2, flags & 4 ? -1 : 0);
}

#endif /* AVFORMAT_ISOM_H */
