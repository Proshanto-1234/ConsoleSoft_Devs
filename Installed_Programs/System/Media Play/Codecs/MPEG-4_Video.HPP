#ifndef MPEGVIDEO_H
#define MPEGVIDEO_H

#include "avcodec.h"
#include "frame.h"
#include "hwcontext.h"
#include "qp_table.h"
#include "ratecontrol.h"
#include "rectangle.h"
#include "thread.h"
#include "dct.h"
#include "put_bits.h"

extern const int ff_zigzag_direct[64];
extern const uint8_t ff_default_intra_matrix[64];
extern const uint8_t ff_default_non_intra_matrix[64];
extern const uint8_t ff_h263_chroma_intra_matrix[64];
extern const uint8_t ff_h263_chroma_non_intra_matrix[64];
extern const uint8_t ff_h263_default_intra_matrix[64];
extern const uint8_t ff_h263_default_non_intra_matrix[64];
extern const uint8_t ff_mpeg2_chroma_intra_matrix[64];
extern const uint8_t ff_mpeg2_chroma_non_intra_matrix[64];
extern const uint8_t ff_mpeg2_default_intra_matrix[64];
extern const uint8_t ff_mpeg2_default_non_intra_matrix[64];

namespace ffmpeg {

typedef struct Picture Structure;
typedef struct ERContext ERContext;

#define MAX_B_FRAMES 16
#define MV_COUNT       5
#define MV_TYPE_16X16 0
#define MV_TYPE_16X8  1
#define MV_TYPE_8X8   2
#define MV_TYPE_FIELD 3

#define MB_TYPE_INTRA    0x0001
#define MB_TYPE_INTER    0x0002
#define MB_TYPE_SKIP     0x0004
#define MB_TYPE_QUANT    0x0008
#define MB_TYPE_MOTION_FORWARD 0x0010
#define MB_TYPE_MOTION_BACKWARD 0x0020
#define MB_TYPE_PATTERN  0x0040
#define MB_TYPE_4VLC     0x0080
#define MB_TYPE_GMC      0x0100
#define MB_TYPE_ACPRED   0x0200
#define MB_TYPE_H_INTRA  0x0400
#define MB_TYPE_V_INTRA  0x0800
#define MB_TYPE_DIRECT2  0x1000
#define MB_TYPE_16x8     0x2000
#define MB_TYPE_8x8      0x4000
#define MB_TYPE_INTERLACED 0x8000
#define MB_TYPE_L0L0     0x00000000U
#define MB_TYPE_L0L1     0x10000000U
#define MB_TYPE_L1L0     0x20000000U
#define MB_TYPE_L1L1     0x30000000U
#define MB_TYPE_PASCALE  0x40000000U
#define MB_TYPE_GLOBAL   0x80000000U
#define MB_TYPE_INTRA_PCM 0x01000000U

#define IS_INTRA(mb_type)    ((mb_type) & MB_TYPE_INTRA)
#define IS_INTER(mb_type)    ((mb_type) & MB_TYPE_INTER)
#define IS_SKIP(mb_type)     ((mb_type) & MB_TYPE_SKIP)
#define IS_QUANT(mb_type)    ((mb_type) & MB_TYPE_QUANT)
#define IS_ACPRED(mb_type)   ((mb_type) & MB_TYPE_ACPRED)
#define IS_4VLC(mb_type)      ((mb_type) & MB_TYPE_4VLC)
#define IS_GMC(mb_type)       ((mb_type) & MB_TYPE_GMC)
#define IS_DIRECT(mb_type)    ((mb_type) & MB_TYPE_DIRECT2)
#define IS_16X8(mb_type)      ((mb_type) & MB_TYPE_16x8)
#define IS_8X8(mb_type)       ((mb_type) & MB_TYPE_8x8)
#define IS_INTERLACED(mb_type) ((mb_type) & MB_TYPE_INTERLACED)
#define IS_INTRA_PCM(mb_type)  ((mb_type) & MB_TYPE_INTRA_PCM)

#define IS_MV_FORWARD(mb_type)  ((mb_type) & MB_TYPE_MOTION_FORWARD)
#define IS_MV_BACKWARD(mb_type) ((mb_type) & MB_TYPE_MOTION_BACKWARD)
#define IS_PASCALE(mb_type)     ((mb_type) & MB_TYPE_PASCALE)
#define IS_GLOBAL(mb_type)      ((mb_type) & MB_TYPE_GLOBAL)

#define MB_CBP_RD 1
#define MB_TYPE_RD 2

#define FF_PROFILE_UNKNOWN -99
#define FF_PROFILE_MPEG2_422 2
#define FF_PROFILE_MPEG2_HIGH 4
#define FF_PROFILE_MPEG2_SS 6
#define FF_PROFILE_MPEG2_SIMPLE 8

#define FF_BUG_AUTODETECT          1
#define FF_BUG_OLD_MSMPEG4         2
#define FF_BUG_XVID_GMC            4
#define FF_BUG_QPEL_CHROMA         8
#define FF_BUG_STD_QPEL            16
#define FF_BUG_UOP_HQC             32
#define FF_BUG_NO_PADDING          64
#define FF_BUG_AMV_VFR             128
#define FF_BUG_AC_VLC              256
#define FF_BUG_GRAY                512
#define FF_BUG_MSMPEG4_BUG         1024
#define FF_BUG_MPEG4_BUG           2048
#define FF_BUG_VCR_BUG             4096
#define FF_BUG_DC_CLIP             8192
#define FF_BUG_ parksons           16384
#define FF_BUG_HPEL_CHROMA         32768
#define FF_BUG_ER_PIVOT            65536
#define FF_BUG_ERROR_CONCEALMENT   131072
#define FF_BUG_BITSTREAM_CLIP      262144
#define FF_BUG_UMP4                524288
#define FF_BUG_border              1048576
#define FF_BUG_DIRECT_BLOCKSIZE    2097152
#define FF_BUG_EDGE                4194304
#define FF_BUG_H263_SEPARATE_MV   8388608
#define FF_BUG_NB                 9 /* last + 1 */

#define FF_DCT_AUTO 0
#define FF_DCT_FASTINT 1
#define FF_DCT_INT 2
#define FF_DCT_MMX 3
#define FF_DCT_ALTIVEC 4
#define FF_DCT_ARMV5TE 5
#define FF_DCT_SH4 6
#define FF_DCT_ARMV6 7
#define FF_DCT_VSX 8
#define FF_DCT_AVX 9
#define FF_DCT_AVX2 10
#define FF_DCT_WASM 11
#define FF_DCT_NB 12

#define FF_IDCT_AUTO 0
#define FF_IDCT_SIMPLE 1
#define FF_IDCT_INT 2
#define FF_IDCT_ARMV4 3
#define FF_IDCT_ARMV5E 4
#define FF_IDCT_MMX 5
#define FF_IDCT_MMX2 6
#define FF_IDCT_3DNOW 7
#define FF_IDCT_3DNOW2 8
#define FF_IDCT_SSE2 9
#define FF_IDCT_ALTIVEC 10
#define FF_IDCT_SH4 11
#define FF_IDCT_ARMV6 12
#define FF_IDCT_NEON 13
#define FF_IDCT_VSX 14
#define FF_IDCT_AVX 15
#define FF_IDCT_AVX2 16
#define FF_IDCT_WASM 17
#define FF_IDCT_NB 18

#define FF_PRED_LEFT   0
#define FF_PRED_PLANE  1
#define FF_PRED_MEDIAN 2

#define FF_ME_ZERO    0
#define FF_ME_EPZS    1
#define FF_ME_XONE    2
#define FF_ME_FULL    3
#define FF_ME_LOG     4
#define FF_ME_PHODS  5
#define FF_ME_TDLS    6
#define FF_ME_RD      7
#define FF_ME_NB      8

#define FF_MB_DECISION_RD   1
#define FF_MB_DECISION_BITS 2

#define FF_COMPLEXITY_SCALE 1024

#define FF_PROFILE_H263_BASELINE          0
#define FF_PROFILE_H263_BACKWARD_COMPATIBLE 1
#define FF_PROFILE_H263_SIGNAL_COMPLEXITY   2
#define FF_PROFILE_H263_ISPV2               3
#define FF_PROFILE_H263_ISPV3               4
#define FF_PROFILE_H263_MAX                 5

#define FF_PROFILE_MPEG4_SIMPLE             0
#define FF_PROFILE_MPEG4_ADVANCED_SIMPLE    1
#define FF_PROFILE_MPEG4_CORE               2
#define FF_PROFILE_MPEG4_MAIN               3
#define FF_PROFILE_MPEG4_N_PRESP_SIMPLE     4
#define FF_PROFILE_MPEG4_SIMPLE_SCALABLE    5
#define FF_PROFILE_MPEG4_BASIC_SCALABLE     6
#define FF_PROFILE_MPEG4_HYBRID             7
#define FF_PROFILE_MPEG4_ADVANCED_CORE      8
#define FF_PROFILE_MPEG4_ADVANCED_SCALABLE  9
#define FF_PROFILE_MPEG4_2D_MESH            10
#define FF_PROFILE_MPEG4_3D_MESH            11
#define FF_PROFILE_MPEG4_FINE_GRAINED_SCAL 12
#define FF_PROFILE_MPEG4_SIMPLE_FSE         13
#define FF_PROFILE_MPEG4_FREEXT_SIMPLE      14
#define FF_PROFILE_MPEG4_FREEXT_SCALABLE    15
#define FF_PROFILE_MPEG4_FREEXT_CORE        16
#define FF_PROFILE_MPEG4_FREEXT_HIGH        17
#define FF_PROFILE_MPEG4_MAX                18

#define FF_LEVEL_UNKNOWN           -99
#define FF_LEVEL_MPEG4_0           0
#define FF_LEVEL_MPEG4_0_5         1
#define FF_LEVEL_MPEG4_1           2
#define FF_LEVEL_MPEG4_2           3
#define FF_LEVEL_MPEG4_3           4
#define FF_LEVEL_MPEG4_4           5
#define FF_LEVEL_MPEG4_5           6
#define FF_LEVEL_MPEG4_MAX         7

#define FF_MB_TYPE_L0 1
#define FF_MB_TYPE_L1 2

#define FF_DEFAULT_QUANT_BIAS 15

#define FF_QP2LAMBDA 11.833519F
#define FF_LAMBDA_MAX 131072

#define FF_CODER_TYPE_VLC   0
#define FF_CODER_TYPE_AC    1
#define FF_CODER_TYPE_RAW   2

#define FF_PROFILE_UNKNOWN -99

/**
 * @ingroup lavc_encdec
 * @{
 */
class MpegEncContext { // Converted struct to class for C++-style, members are kept public for now
public:
    AVCodecContext *avctx;
    Picture *current_picture_ptr;
    Picture current_picture;
    Picture next_picture;
    Picture last_picture;
    Picture last_picture2;
    Picture *ref_pic[4][2];
    Picture *motion_refs[2];
    AVFrame *coded_frame;

    int mb_width;      ///< number of macroblocks in a row
    int mb_height;     ///< number of macroblocks in a column
    int mb_num;        ///< number of macroblocks
    int mb_stride;     ///< macroblock row stride
    int b8_stride;     ///< block8 row stride (mb_stride*2)
    int block_wrap[3];

    /* current mb pos */
    int mb_x;
    int mb_y;
    int block_x[6];
    int block_y[6];
    int block_index[6];
    int b8_x;
    int b8_y;

    uint8_t *img_buffer[3];     ///< aligned image lines
    uint8_t *current_frame[3];   ///< aligned current_frame lines
    uint8_t *last_frame[3];      ///< aligned last_frame lines
    uint8_t *last_frame2[3];     ///< aligned last_frame2 lines
    uint8_t *next_frame[3];      ///< aligned next_frame lines

    uint8_t *draw_buffer[3];
    uint8_t *dest[3];           ///< aligned dest lines

    int current_motion_vector_table;

    /* motion vectors of current mb/block8 */
    int mv[2][MV_COUNT][2];     ///< motion_val[list][mv_index][xy]

    /* last motion vector predictors */
    int last_mv[2][2][2];     ///< last_mv[list][mv_index][xy]

    /* motion vectors of last frame for motion compensation (needed for bi-dir) */
    int (*motion_val[2])[4*16*16][2]; ///< motion_val[list][block_index][xy]

    /* motion vectors of previous frame for direct mv computation */
    int (*p_field_mv_table[2])[2*16*8][2]; /* FIXME merge p_field_mv_table & motion_val */

    int direct_scale_mv[2][2*MV_RANGE+1];

    /* motion type (MV_TYPE_...) */
    int mv_type;

    /* macroblock type (MB_TYPE_...) */
    uint32_t mb_type[16*16];     ///< mb_type[mb_index]

    /* macroblock qp - needed for ratecontrol */
    int qscale_table[16*16 + 1]; ///< qscale_table[mb_index]

    /* macroblock qp for ratecontrol (used for alternate qp) */
    int rc_mb_qp_store[16*16];  ///< rc_mb_qp_store[mb_index]

    /* macroblock qp for ratecontrol (used for alternate qp in P-frames) */
    int p_qscale_table[16*16];  ///< p_qscale_table[mb_index]

    /* motion vector field select for bi-predictive motion compensation */
    int field_select[2][2];       ///< field_select[list][mv_index]

    int current_block_offset[6];
    int block_offset[9*3];

    int intra_quant_bias;
    int inter_quant_bias;
    uint16_t intra_matrix[64];      ///< custom intra quant matrix
    uint16_t chroma_intra_matrix[64]; ///< custom chroma intra quant matrix
    uint16_t inter_matrix[64];      ///< custom inter quant matrix
    uint16_t chroma_inter_matrix[64]; ///< custom chroma inter quant matrix
    uint16_t flat_matrix8[64];        ///< flat 8 matrix
    uint16_t flat_matrix16[64];       ///< flat 16 matrix

    int q_scale_type;     ///< 0: same qscale, 1: H.263, 2: MPEG-4
    int chroma_q_offset;
    int custom_mv_pred;

    int pict_type;        ///< current picture type (AV_PICTURE_TYPE_...)
    int coded_picture_number;
    int current_picture_number;
    int frame_number;     ///< frame_number modulo gop_size
    int gop_size;
    int b_frame_count;
    int last_intra_coded_frame;
    int last_non_b_pict_coded_frame;
    int last_p_frame_coded_frame;
    int prev_pict_type;

    int time_incr_bits;
    int vop_time_increment;
    int vo_type;
    int vol_control_parameters_flag;
    int vol_sprite_usage;
    int sprite_brightness_formulae;
    int sprite_transform_type;
    int sprite_warping_points;
    int sprite_mv_per_gvop;
    int sprite_amc_multiframes;
    int sprite_achura_mv_accuracy;
    int sprite_width;
    int sprite_height;
    int sprite_base_width;
    int sprite_base_height;
    int sprite_base_id;
    int low_latency_mpeg4;
    int data_partitioning;
    int resync_marker;
    int error_resilience;
    int rv10_version;
    int interlaced_dct;
    int alternate_vertical_scan_flag;
    int top_field_first;
    int quarter_sample;
    int loop_filter;
    int complexity_estimate;
    int intra_dc_precision;
    int trucated_vbv;
    int signed_rnd;
    int gray_scale;
    int reduced_still_picture_header;
    int fast_unblock_dct;
    int aic;
    int progressive_sequence;
    int progressive_frame;
    int concealment_motion_vectors;
    int rounding_control;
    int closed_gop;
    int broken_link;
    int chroma_420_type;
    int obmc;
    int overlapped_transform;
    int sprite_usage_base;
    int warppoint_iterations;
    int scalability_vop_coded;
    int quant_precision;
    int object_layer_shape;
    int video_object_layer_width;
    int video_object_layer_height;
    int shape_coding_type;
    int video_object_layer_shape_extension;
    int vোষ_increment_bits;
    int fixed_vop_rate;
    int fixed_vop_time_increment;
    int direct_mv_count;
    int num_sprite_warping_points;
    int quant_type;
    int complexity_estimation_disable;
    int resync_inter_mb_qp;
    int resync_intra_mb_qp;
    int data_partitioned_sync;
    int reversible_vlc;
    int max_bframes;
    int trellis;
    int use_mv0;
    int b_quant_offset;
    int chroma_intra_offset;
    int scene_change_score;
    int progressive_dct;
    int alt_quant;
    int h263_aic;
    int h263_plus_aic;
    int mod4_mv;
    int slice_count;
    int slices_per_frame;
    int mb_cmp_table[256];
    int mb_cmp_penalty;
    int skip_top;
    int skip_bottom;
    int skip_left;
    int skip_right;
    int d量t8x8_algo;
    int intra_vlc_format;
    int inter_vlc_format;
    int mv_bits;
    int dc_val[3];
    int intra_mode_base;
    int intra_mode_chroma;
    int luma_elim_threshold;
    int chroma_elim_threshold;
    int max_pixels_threshold;
    int max_pixels_threshold_chroma;
    int mb_skipped_rate_est;
    int mb_non_skipped_rate_est;
    int mv_scale;
    int mpeg_quant;
    int rtp_payload_size;
    int me_penalty_compensation;
    int me_pre;
    int sub_q_scale_table_offset;
    int inter_matrix_level;
    int intra_matrix_level;

    int lambda;
    int lambda_min;
    int lambda_max;
    int lambda2;
    int lambda_for[3];
    int lambda_last_for[3];
    int mb_lambda_table[16*16];    ///< mb_lambda_table[mb_index]
    int mb_lambda_intra_table[16*16]; ///< mb_lambda_intra_table[mb_index]

    int f_code;
    int b_code;

    int pp_time;
    int pb_time;
    int pp_field_time;
    int pb_field_time;

    PutBitContext pb;
    uint8_t *bitstream;
    int bitstream_size;
    int bitstream_index;
    int last_bits;

    uint8_t *current_gob;
    uint8_t *current_slice;
    uint8_t *mb_bitstream;
    uint8_t *mb_mb_type_base;
    uint8_t *mb_mcbpc_base;
    uint8_t *mb_cbp_base;
    uint8_t *mb_mvd_base;
    uint8_t *mb_ac_coeff_base;
    uint8_t *mb_intra_modes_base;
    uint8_t *mb_skipped_base;
    uint8_t *mb_motion_base;

    uint8_t *ptr_gob_start_code;
    uint8_t *ptr_slice_start_code;
    uint8_t *ptr_mb_current_end;
    uint8_t *ptr_mb_start;
    uint8_t *ptr_mb_end;
    uint8_t *ptr_mb_field_decisions;
    uint8_t *ptr_mb_type;
    uint8_t *ptr_mcbpc;
    uint8_t *ptr_cbp;
    uint8_t *ptr_mvd;
    uint8_t *ptr_ac_coeff;
    uint8_t *ptr_dc_coeff;
    uint8_t *ptr_intra_modes;
    uint8_t *ptr_skipped;
    uint8_t *ptr_motion;
    uint8_t *ptr_motion_val;
    uint8_t *ptr_motion_val_tmp;
    uint8_t *ptr_er_temp;
    uint8_t *ptr_mb_index2xy;
    uint8_t *ptr_gob_index;
    uint8_t *ptr_lastgob;
    int16_t (*pblocks[12])[64];

    int16_t (*block)[64]; ///< points to one of the following blocks
    int16_t (*blocks)[12][64]; // for HQ mode we need to keep the best block
    int (*decode_mb)(struct MpegEncContext *s, int16_t block[6][64]); // used by some codecs to avoid a switch()
#define SLICE_OK         0
#define SLICE_ERROR     -1
#define SLICE_END       -2 ///<end marker found
#define SLICE_NOEND     -3 ///<no end marker or error found but mb count exceeded

    void (*dct_unquantize_mpeg1_intra)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_mpeg1_inter)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_mpeg2_intra)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_mpeg2_inter)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_h263_intra)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_h263_inter)(struct MpegEncContext *s,
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_intra)(struct MpegEncContext *s, // unquantizer to use (MPEG-4 can use both)
                           int16_t *block/*align 16*/, int n, int qscale);
    void (*dct_unquantize_inter)(struct MpegEncContext *s, // unquantizer to use (MPEG-4 can use both)
                           int16_t *block/*align 16*/, int n, int qscale);
    int (*dct_quantize)(struct MpegEncContext *s, int16_t *block/*align 16*/, int n, int qscale, int *overflow);
    int (*fast_dct_quantize)(struct MpegEncContext *s, int16_t *block/*align 16*/, int n, int qscale, int *overflow);
    void (*denoise_dct)(struct MpegEncContext *s, int16_t *block);

    int mpv_flags;      ///< flags set by private options
    int quantizer_noise_shaping;

    /**
     * ratecontrol qmin qmax limiting method
     * 0-> clipping, 1-> use a nice continuous function to limit qscale within qmin/qmax.
     */
    float rc_qsquish;
    float rc_qmod_amp;
    int   rc_qmod_freq;
    float rc_initial_cplx;
    float rc_buffer_aggressivity;
    float border_masking;
    int lmin, lmax;

    char *rc_eq;

    /* temp buffers for rate control */
    float *cplx_tab, *bits_tab;

    /* flag to indicate a reinitialization is required, e.g. after
     * a frame size change */
    int context_reinit;

    ERContext er;

    int error_rate;

    /* temporary frames used by b_frame_strategy = 2 */
    AVFrame *tmp_frames[MAX_B_FRAMES + 2];
    int b_frame_strategy;
    int b_sensitivity;

    /* frame skip options for encoding */
    int frame_skip_threshold;
    int frame_skip_factor;
    int frame_skip_exp;
    int frame_skip_cmp;

    int scenechange_threshold;
    int noise_reduction;
}; // MpegEncContext is now a class

/* mpegvideo_enc common options */
#define FF_MPV_FLAG_SKIP_RD      0x0001
#define FF_MPV_FLAG_STRICT_GOP   0x0002
#define FF_MPV_FLAG_QP_RD        0x0004
#define FF_MPV_FLAG_CBP_RD       0x0008
#define FF_MPV_FLAG_NAQ          0x0010
#define FF_MPV_FLAG_MV0          0x0020

#define FF_MPV_OPT_CMP_FUNC \
{ "sad",    "Sum of absolute differences, fast", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SAD }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "sse",    "Sum of squared errors", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SSE }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "satd",   "Sum of absolute Hadamard transformed differences", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_SATD }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "dct",    "Sum of absolute DCT transformed differences", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_DCT }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "psnr",   "Sum of squared quantization errors, low quality", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_PSNR }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "bit",    "Number of bits needed for the block", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_BIT }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "rd",     "Rate distortion optimal, slow", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_RD }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "zero",   "Zero", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_ZERO }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "vsad",   "Sum of absolute vertical differences", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_VSAD }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "vsse",   "Sum of squared vertical differences", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_VSSE }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "nsse",   "Noise preserving sum of squared differences", 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_NSSE }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "dct264", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_DCT264 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "dctmax", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_DCTMAX }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }, \
{ "chroma", NULL, 0, AV_OPT_TYPE_CONST, {.i64 = FF_CMP_CHROMA }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" }

#define FF_MPV_OFFSET(x) offsetof(MpegEncContext, x)
#define FF_MPV_OPT_FLAGS (AV_OPT_FLAG_VIDEO_PARAM | AV_OPT_FLAG_ENCODING_PARAM)
#define FF_MPV_COMMON_OPTS \
FF_MPV_OPT_CMP_FUNC, \
{ "mpv_flags",      "Flags common for all mpegvideo-based encoders.", FF_MPV_OFFSET(mpv_flags), AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "skip_rd",        "RD optimal MB level residual skipping", 0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_SKIP_RD },    0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "strict_gop",     "Strictly enforce gop size",             0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_STRICT_GOP }, 0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "qp_rd",          "Use rate distortion optimization for qp selection", 0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_QP_RD },  0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "cbp_rd",         "use rate distortion optimization for CBP",          0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_CBP_RD }, 0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "naq",            "normalize adaptive quantization",                   0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_NAQ },    0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "mv0",            "always try a mb with mv=<0,0>",                     0, AV_OPT_TYPE_CONST, { .i64 = FF_MPV_FLAG_MV0 },    0, 0, FF_MPV_OPT_FLAGS, "mpv_flags" },\
{ "luma_elim_threshold",   "single coefficient elimination threshold for luminance (negative values also consider dc coefficient)",\
                                                                      FF_MPV_OFFSET(luma_elim_threshold), AV_OPT_TYPE_INT, { .i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{ "chroma_elim_threshold", "single coefficient elimination threshold for chrominance (negative values also consider dc coefficient)",\
                                                                      FF_MPV_OFFSET(chroma_elim_threshold), AV_OPT_TYPE_INT, { .i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{ "quantizer_noise_shaping", NULL,                                 FF_MPV_OFFSET(quantizer_noise_shaping), AV_OPT_TYPE_INT, { .i64 = 0 },       0, INT_MAX, FF_MPV_OPT_FLAGS },\
{ "error_rate", "Simulate errors in the bitstream to test error concealment.",                                                                                                 \
                                                                    FF_MPV_OFFSET(error_rate),              AV_OPT_TYPE_INT, { .i64 = 0 },       0, INT_MAX, FF_MPV_OPT_FLAGS },\
{"qsquish", "how to keep quantizer between qmin and qmax (0 = clip, 1 = use differentiable function)",                                                                         \
                                                                    FF_MPV_OFFSET(rc_qsquish), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, 0, 99, FF_MPV_OPT_FLAGS},                      \
{"rc_qmod_amp", "experimental quantizer modulation",               FF_MPV_OFFSET(rc_qmod_amp), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, FF_MPV_OPT_FLAGS},         \
{"rc_qmod_freq", "experimental quantizer modulation",              FF_MPV_OFFSET(rc_qmod_freq), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS},            \
{"rc_eq", "Set rate control equation. When computing the expression, besides the standard functions \"                                                                          \
          "defined in the section 'Expression Evaluation', the following functions are available: "                                                                            \
          "bits2qp(bits), qp2bits(qp). Also the following constants are available: iTex pTex tex mv "                                                                          \
          "fCode iCount mcVar var isI isP isB avgQP qComp avgIITex avgPITex avgPPTex avgBPTex avgTex.",                                                                        \
                                                                    FF_MPV_OFFSET(rc_eq), AV_OPT_TYPE_STRING,                          .flags = FF_MPV_OPT_FLAGS },           \
{"rc_init_cplx", "initial complexity for 1-pass encoding",         FF_MPV_OFFSET(rc_initial_cplx), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, FF_MPV_OPT_FLAGS},      \
{"rc_buf_aggressivity", "currently useless",                       FF_MPV_OFFSET(rc_buffer_aggressivity), AV_OPT_TYPE_FLOAT, {.dbl = 1.0 }, -FLT_MAX, FLT_MAX, FF_MPV_OPT_FLAGS},\
{"border_mask", "increase the quantizer for macroblocks close to borders", FF_MPV_OFFSET(border_masking), AV_OPT_TYPE_FLOAT, {.dbl = 0 }, -FLT_MAX, FLT_MAX, FF_MPV_OPT_FLAGS},   \
{"lmin", "minimum Lagrange factor (VBR)",                          FF_MPV_OFFSET(lmin), AV_OPT_TYPE_INT, {.i64 =  2*FF_QP2LAMBDA }, 0, INT_MAX, FF_MPV_OPT_FLAGS },           \
{"lmax", "maximum Lagrange factor (VBR)",                          FF_MPV_OFFSET(lmax), AV_OPT_TYPE_INT, {.i64 = 31*FF_QP2LAMBDA }, 0, INT_MAX, FF_MPV_OPT_FLAGS },           \
{"ibias", "intra quant bias",                                      FF_MPV_OFFSET(intra_quant_bias), AV_OPT_TYPE_INT, {.i64 = FF_DEFAULT_QUANT_BIAS }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },  \
{"pbias", "inter quant bias",                                      FF_MPV_OFFSET(inter_quant_bias), AV_OPT_TYPE_INT, {.i64 = FF_DEFAULT_QUANT_BIAS }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },  \
{"rc_strategy", "ratecontrol method",                              FF_MPV_OFFSET(rc_strategy), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, 1, FF_MPV_OPT_FLAGS },  \
{"motion_est", "motion estimation algorithm",                      FF_MPV_OFFSET(motion_est), AV_OPT_TYPE_INT, {.i64 = FF_ME_EPZS }, FF_ME_ZERO, FF_ME_XONE, FF_MPV_OPT_FLAGS, "motion_est" },  \
{ "zero", NULL, 0, AV_OPT_TYPE_CONST, { .i64 = FF_ME_ZERO }, 0, 0, FF_MPV_OPT_FLAGS, "motion_est" }, \
{ "epzs", NULL, 0, AV_OPT_TYPE_CONST, { .i64 = FF_ME_EPZS }, 0, 0, FF_MPV_OPT_FLAGS, "motion_est" }, \
{ "xone", NULL, 0, AV_OPT_TYPE_CONST, { .i64 = FF_ME_XONE }, 0, 0, FF_MPV_OPT_FLAGS, "motion_est" }, \
{"b_strategy", "Strategy to choose between I/P/B-frames",          FF_MPV_OFFSET(b_frame_strategy), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, 2, FF_MPV_OPT_FLAGS },\
{"b_sensitivity", "Adjust sensitivity of b_frame_strategy 1",      FF_MPV_OFFSET(b_sensitivity), AV_OPT_TYPE_INT, {.i64 = 40 }, 1, INT_MAX, FF_MPV_OPT_FLAGS },\
{"brd_scale", "Downscale frames for dynamic B-frame decision",     FF_MPV_OFFSET(brd_scale), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, 3, FF_MPV_OPT_FLAGS },\
{"skip_threshold", "Frame skip threshold",                         FF_MPV_OFFSET(frame_skip_threshold), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"skip_factor", "Frame skip factor",                               FF_MPV_OFFSET(frame_skip_factor), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"skip_exp", "Frame skip exponent",                              FF_MPV_OFFSET(frame_skip_exp), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"skip_cmp", "Frame skip compare function",                        FF_MPV_OFFSET(frame_skip_cmp), AV_OPT_TYPE_INT, {.i64 = FF_CMP_DCTMAX }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS, "cmp_func" },\
{"sc_threshold", "Scene change threshold",                         FF_MPV_OFFSET(scenechange_threshold), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"noise_reduction", "Noise reduction",                             FF_MPV_OFFSET(noise_reduction), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"mpeg_quant", "Use MPEG quantizers instead of H.263",             FF_MPV_OFFSET(mpeg_quant), AV_OPT_TYPE_INT, {.i64 = 0 }, 0, 1, FF_MPV_OPT_FLAGS },\
{"ps", "RTP payload size in bytes",                            FF_MPV_OFFSET(rtp_payload_size), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"mepc", "Motion estimation bitrate penalty compensation (1.0 = 256)", FF_MPV_OFFSET(me_penalty_compensation), AV_OPT_TYPE_INT, {.i64 = 256 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },\
{"mepre", "pre motion estimation", FF_MPV_OFFSET(me_pre), AV_OPT_TYPE_INT, {.i64 = 0 }, INT_MIN, INT_MAX, FF_MPV_OPT_FLAGS },

extern const AVOption ff_mpv_generic_options[];

/**
 * Set the given MpegEncContext to common defaults (same for encoding
 * and decoding).  The changed fields will not depend upon the prior
 * state of the MpegEncContext.
 */
extern void ff_mpv_common_defaults(ffmpeg::MpegEncContext *s);

extern int ff_mpv_common_init(ffmpeg::MpegEncContext *s);
extern void ff_mpv_common_init_arm(ffmpeg::MpegEncContext *s);
extern void ff_mpv_common_init_neon(ffmpeg::MpegEncContext *s);
extern void ff_mpv_common_init_ppc(ffmpeg::MpegEncContext *s);
extern void ff_mpv_common_init_x86(ffmpeg::MpegEncContext *s);

extern int ff_mpv_common_frame_size_change(ffmpeg::MpegEncContext *s);
extern void ff_mpv_common_end(ffmpeg::MpegEncContext *s);

extern void ff_mpv_decode_defaults(ffmpeg::MpegEncContext *s);
extern void ff_mpv_decode_mb(ffmpeg::MpegEncContext *s, int16_t block[12][64]);
extern void ff_mpv_report_decode_progress(ffmpeg::MpegEncContext *s);

extern int ff_mpv_frame_start(ffmpeg::MpegEncContext *s, AVCodecContext *avctx);
extern void ff_mpv_frame_end(ffmpeg::MpegEncContext *s);

extern int ff_mpv_encode_init(AVCodecContext *avctx);
extern void ff_mpv_encode_init_x86(ffmpeg::MpegEncContext *s);

extern int ff_mpv_encode_end(AVCodecContext *avctx);
extern int ff_mpv_encode_picture(AVCodecContext *avctx, AVPacket *pkt,
                          const AVFrame *frame, int *got_packet);

extern void ff_clean_intra_table_entries(ffmpeg::MpegEncContext *s);
extern void ff_mpeg_draw_horiz_band(ffmpeg::MpegEncContext *s, int y, int h);
extern void ff_mpeg_flush(AVCodecContext *avctx);
extern void ff_print_debug_info(ffmpeg::MpegEncContext *s, Picture *p);
extern void ff_write_quant_matrix(PutBitContext *pb, uint16_t *matrix);

extern int ff_update_duplicate_context(ffmpeg::MpegEncContext *dst, ffmpeg::MpegEncContext *src);
extern int ff_mpeg_update_thread_context(AVCodecContext *dst, const AVCodecContext *src);
extern void ff_set_qscale(ffmpeg::MpegEncContext * s, int qscale);

extern void ff_mpv_idct_init(ffmpeg::MpegEncContext *s);
extern void ff_convert_matrix(ffmpeg::MpegEncContext *s, int (*qmat)[64], uint16_t (*qmat16)[2][64],
                       const uint16_t *quant_matrix, int bias, int qmin, int qmax, int intra);
extern int ff_dct_quantize_c(ffmpeg::MpegEncContext *s, int16_t *block, int n, int qscale, int *overflow);

extern void ff_init_block_index(ffmpeg::MpegEncContext *s);

extern void ff_mpv_motion(ffmpeg::MpegEncContext *s,
                   uint8_t *dest_y, uint8_t *dest_cb,
                   uint8_t *dest_cr, int dir,
                   uint8_t **ref_picture,
                   op_pixels_func (*pix_op)[4],
                   qpel_mc_func (*qpix_op)[16]);

extern inline void ff_update_block_index(ffmpeg::MpegEncContext *s);
extern inline int get_bits_diff(ffmpeg::MpegEncContext *s);

} // namespace ffmpeg

#endif /* AVCODEC_MPEGVIDEO_H */
