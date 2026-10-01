/*
 * Copyright (c) 2017, Alliance for Open Media. All rights reserved.
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */
#ifndef AOM_AV1_DECODER_INSPECTION_H_
#define AOM_AV1_DECODER_INSPECTION_H_

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "av1/common/seg_common.h"
#if CONFIG_ACCOUNTING
#include "av1/decoder/accounting.h"
#endif

#ifndef AOM_AOM_AOMDX_H_
typedef void (*aom_inspect_cb)(void *decoder, void *data);
#endif

typedef struct insp_mv insp_mv;

struct insp_mv {
  int16_t row;
  int16_t col;
};

typedef struct insp_mi_data insp_mi_data;

struct insp_mi_data {
  insp_mv mv[2];
  // videoparser: Motion vector difference (coded delta)
  insp_mv mvd[2];
  int16_t ref_frame[2];
  int16_t mode;
  int16_t uv_mode;
  int16_t bsize;
  int16_t skip;
  int16_t segment_id;
  int16_t dual_filter_type;
  int16_t filter[2];
  int16_t tx_type;
  int16_t tx_size;
  int16_t cdef_level;
  int16_t cdef_strength;
  int16_t cfl_alpha_idx;
  int16_t cfl_alpha_sign;
  int16_t current_qindex;
  int16_t compound_type;
  int16_t motion_mode;
  int16_t intrabc;
  int16_t palette;
  int16_t uv_palette;
  // videoparser: QP index with the segment feature applied
  int16_t vp_qindex;
  // videoparser: bits of the block this 4x4 unit belongs to (in 1/8 bits),
  // and the position of the block (in 4x4 units)
  uint32_t vp_total_bits;
  uint32_t vp_motion_bits;
  uint32_t vp_coeff_bits;
  int vp_mi_row;
  int vp_mi_col;
};

typedef struct insp_frame_data insp_frame_data;

struct insp_frame_data {
#if CONFIG_ACCOUNTING
  Accounting *accounting;
#endif
  insp_mi_data *mi_grid;
  int16_t frame_number;
  int show_frame;
  int frame_type;
  int base_qindex;
  int mi_rows;
  int mi_cols;
  int tile_mi_rows;
  int tile_mi_cols;
  int16_t y_dequant[MAX_SEGMENTS][2];
  int16_t u_dequant[MAX_SEGMENTS][2];
  int16_t v_dequant[MAX_SEGMENTS][2];
  // TODO(negge): add per frame CDEF data
  int delta_q_present_flag;
  int delta_q_res;
  int show_existing_frame;
  // videoparser: Bit counts for motion and coefficient decoding
  uint64_t motion_bits;
  uint64_t coef_bits;
  // videoparser: decoder frame buffer of the decoded frame, to find the
  // frame again when it is output (aom_image_t.vp_frame_key), also with
  // show_existing_frame
  const void *vp_frame_key;
};

void ifd_init(insp_frame_data *fd, int frame_width, int frame_height);
void ifd_clear(insp_frame_data *fd);
int ifd_inspect(insp_frame_data *fd, void *decoder, int skip_not_transform);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
#endif  // AOM_AV1_DECODER_INSPECTION_H_
