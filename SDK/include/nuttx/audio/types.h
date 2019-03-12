
#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>
#include <stdio.h>

#define PRId64 "lld"
#define PRIu64 "llu"
#define PRIX64 "llx"
#define NULL_IF_CONFIG_SMALL(x)	(x)

#define MKTAG(a,b,c,d)          ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define MKBETAG(a,b,c,d)        ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))

typedef enum __AVCodecID {
    AV_CODEC_ID_NONE,

    /* video codecs */
    AV_CODEC_ID_MPEG1VIDEO,
    AV_CODEC_ID_MPEG2VIDEO, ///< preferred ID for MPEG-1/2 video decoding
#ifdef FF_API_XVMC
    AV_CODEC_ID_MPEG2VIDEO_XVMC,
#endif /* FF_API_XVMC */
    AV_CODEC_ID_H261,
    AV_CODEC_ID_H263,
    AV_CODEC_ID_RV10,
    AV_CODEC_ID_RV20,
    AV_CODEC_ID_MJPEG,
    AV_CODEC_ID_MJPEGB,
    AV_CODEC_ID_LJPEG,
    AV_CODEC_ID_SP5X,
    AV_CODEC_ID_JPEGLS,
    AV_CODEC_ID_MPEG4,
    AV_CODEC_ID_RAWVIDEO,
    AV_CODEC_ID_MSMPEG4V1,
    AV_CODEC_ID_MSMPEG4V2,
    AV_CODEC_ID_MSMPEG4V3,
    AV_CODEC_ID_WMV1,
    AV_CODEC_ID_WMV2,
    AV_CODEC_ID_H263P,
    AV_CODEC_ID_H263I,
    AV_CODEC_ID_FLV1,
    AV_CODEC_ID_SVQ1,
    AV_CODEC_ID_SVQ3,
    AV_CODEC_ID_DVVIDEO,
    AV_CODEC_ID_HUFFYUV,
    AV_CODEC_ID_CYUV,
    AV_CODEC_ID_H264,
    AV_CODEC_ID_INDEO3,
    AV_CODEC_ID_VP3,
    AV_CODEC_ID_THEORA,
    AV_CODEC_ID_ASV1,
    AV_CODEC_ID_ASV2,
    AV_CODEC_ID_FFV1,
    AV_CODEC_ID_4XM,
    AV_CODEC_ID_VCR1,
    AV_CODEC_ID_CLJR,
    AV_CODEC_ID_MDEC,
    AV_CODEC_ID_ROQ,
    AV_CODEC_ID_INTERPLAY_VIDEO,
    AV_CODEC_ID_XAN_WC3,
    AV_CODEC_ID_XAN_WC4,
    AV_CODEC_ID_RPZA,
    AV_CODEC_ID_CINEPAK,
    AV_CODEC_ID_WS_VQA,
    AV_CODEC_ID_MSRLE,
    AV_CODEC_ID_MSVIDEO1,
    AV_CODEC_ID_IDCIN,
    AV_CODEC_ID_8BPS,
    AV_CODEC_ID_SMC,
    AV_CODEC_ID_FLIC,
    AV_CODEC_ID_TRUEMOTION1,
    AV_CODEC_ID_VMDVIDEO,
    AV_CODEC_ID_MSZH,
    AV_CODEC_ID_ZLIB,
    AV_CODEC_ID_QTRLE,
    AV_CODEC_ID_TSCC,
    AV_CODEC_ID_ULTI,
    AV_CODEC_ID_QDRAW,
    AV_CODEC_ID_VIXL,
    AV_CODEC_ID_QPEG,
    AV_CODEC_ID_PNG,
    AV_CODEC_ID_PPM,
    AV_CODEC_ID_PBM,
    AV_CODEC_ID_PGM,
    AV_CODEC_ID_PGMYUV,
    AV_CODEC_ID_PAM,
    AV_CODEC_ID_FFVHUFF,
    AV_CODEC_ID_RV30,
    AV_CODEC_ID_RV40,
    AV_CODEC_ID_VC1,
    AV_CODEC_ID_WMV3,
    AV_CODEC_ID_LOCO,
    AV_CODEC_ID_WNV1,
    AV_CODEC_ID_AASC,
    AV_CODEC_ID_INDEO2,
    AV_CODEC_ID_FRAPS,
    AV_CODEC_ID_TRUEMOTION2,
    AV_CODEC_ID_BMP,
    AV_CODEC_ID_CSCD,
    AV_CODEC_ID_MMVIDEO,
    AV_CODEC_ID_ZMBV,
    AV_CODEC_ID_AVS,
    AV_CODEC_ID_SMACKVIDEO,
    AV_CODEC_ID_NUV,
    AV_CODEC_ID_KMVC,
    AV_CODEC_ID_FLASHSV,
    AV_CODEC_ID_CAVS,
    AV_CODEC_ID_JPEG2000,
    AV_CODEC_ID_VMNC,
    AV_CODEC_ID_VP5,
    AV_CODEC_ID_VP6,
    AV_CODEC_ID_VP6F,
    AV_CODEC_ID_TARGA,
    AV_CODEC_ID_DSICINVIDEO,
    AV_CODEC_ID_TIERTEXSEQVIDEO,
    AV_CODEC_ID_TIFF,
    AV_CODEC_ID_GIF,
    AV_CODEC_ID_DXA,
    AV_CODEC_ID_DNXHD,
    AV_CODEC_ID_THP,
    AV_CODEC_ID_SGI,
    AV_CODEC_ID_C93,
    AV_CODEC_ID_BETHSOFTVID,
    AV_CODEC_ID_PTX,
    AV_CODEC_ID_TXD,
    AV_CODEC_ID_VP6A,
    AV_CODEC_ID_AMV,
    AV_CODEC_ID_VB,
    AV_CODEC_ID_PCX,
    AV_CODEC_ID_SUNRAST,
    AV_CODEC_ID_INDEO4,
    AV_CODEC_ID_INDEO5,
    AV_CODEC_ID_MIMIC,
    AV_CODEC_ID_RL2,
    AV_CODEC_ID_ESCAPE124,
    AV_CODEC_ID_DIRAC,
    AV_CODEC_ID_BFI,
    AV_CODEC_ID_CMV,
    AV_CODEC_ID_MOTIONPIXELS,
    AV_CODEC_ID_TGV,
    AV_CODEC_ID_TGQ,
    AV_CODEC_ID_TQI,
    AV_CODEC_ID_AURA,
    AV_CODEC_ID_AURA2,
    AV_CODEC_ID_V210X,
    AV_CODEC_ID_TMV,
    AV_CODEC_ID_V210,
    AV_CODEC_ID_DPX,
    AV_CODEC_ID_MAD,
    AV_CODEC_ID_FRWU,
    AV_CODEC_ID_FLASHSV2,
    AV_CODEC_ID_CDGRAPHICS,
    AV_CODEC_ID_R210,
    AV_CODEC_ID_ANM,
    AV_CODEC_ID_BINKVIDEO,
    AV_CODEC_ID_IFF_ILBM,
#define AV_CODEC_ID_IFF_BYTERUN1 AV_CODEC_ID_IFF_ILBM
    AV_CODEC_ID_KGV1,
    AV_CODEC_ID_YOP,
    AV_CODEC_ID_VP8,
    AV_CODEC_ID_PICTOR,
    AV_CODEC_ID_ANSI,
    AV_CODEC_ID_A64_MULTI,
    AV_CODEC_ID_A64_MULTI5,
    AV_CODEC_ID_R10K,
    AV_CODEC_ID_MXPEG,
    AV_CODEC_ID_LAGARITH,
    AV_CODEC_ID_PRORES,
    AV_CODEC_ID_JV,
    AV_CODEC_ID_DFA,
    AV_CODEC_ID_WMV3IMAGE,
    AV_CODEC_ID_VC1IMAGE,
    AV_CODEC_ID_UTVIDEO,
    AV_CODEC_ID_BMV_VIDEO,
    AV_CODEC_ID_VBLE,
    AV_CODEC_ID_DXTORY,
    AV_CODEC_ID_V410,
    AV_CODEC_ID_XWD,
    AV_CODEC_ID_CDXL,
    AV_CODEC_ID_XBM,
    AV_CODEC_ID_ZEROCODEC,
    AV_CODEC_ID_MSS1,
    AV_CODEC_ID_MSA1,
    AV_CODEC_ID_TSCC2,
    AV_CODEC_ID_MTS2,
    AV_CODEC_ID_CLLC,
    AV_CODEC_ID_MSS2,
    AV_CODEC_ID_VP9,
    AV_CODEC_ID_AIC,
    AV_CODEC_ID_ESCAPE130,
    AV_CODEC_ID_G2M,
    AV_CODEC_ID_WEBP,
    AV_CODEC_ID_HNM4_VIDEO,
    AV_CODEC_ID_HEVC,
#define AV_CODEC_ID_H265 AV_CODEC_ID_HEVC
    AV_CODEC_ID_FIC,
    AV_CODEC_ID_ALIAS_PIX,
    AV_CODEC_ID_BRENDER_PIX,
    AV_CODEC_ID_PAF_VIDEO,
    AV_CODEC_ID_EXR,
    AV_CODEC_ID_VP7,
    AV_CODEC_ID_SANM,
    AV_CODEC_ID_SGIRLE,
    AV_CODEC_ID_MVC1,
    AV_CODEC_ID_MVC2,
    AV_CODEC_ID_HQX,
    AV_CODEC_ID_TDSC,
    AV_CODEC_ID_HQ_HQA,
    AV_CODEC_ID_HAP,
    AV_CODEC_ID_DDS,
    AV_CODEC_ID_DXV,
    AV_CODEC_ID_SCREENPRESSO,
    AV_CODEC_ID_RSCC,

    AV_CODEC_ID_Y41P = 0x8000,
    AV_CODEC_ID_AVRP,
    AV_CODEC_ID_012V,
    AV_CODEC_ID_AVUI,
    AV_CODEC_ID_AYUV,
    AV_CODEC_ID_TARGA_Y216,
    AV_CODEC_ID_V308,
    AV_CODEC_ID_V408,
    AV_CODEC_ID_YUV4,
    AV_CODEC_ID_AVRN,
    AV_CODEC_ID_CPIA,
    AV_CODEC_ID_XFACE,
    AV_CODEC_ID_SNOW,
    AV_CODEC_ID_SMVJPEG,
    AV_CODEC_ID_APNG,
    AV_CODEC_ID_DAALA,
    AV_CODEC_ID_CFHD,

    /* various PCM "codecs" */
    AV_CODEC_ID_FIRST_AUDIO = 0x10000,     ///< A dummy id pointing at the start of audio codecs
    AV_CODEC_ID_PCM_S16LE = 0x10000,
    AV_CODEC_ID_PCM_S16BE,
    AV_CODEC_ID_PCM_U16LE,
    AV_CODEC_ID_PCM_U16BE,
    AV_CODEC_ID_PCM_S8,
    AV_CODEC_ID_PCM_U8,
    AV_CODEC_ID_PCM_MULAW,
    AV_CODEC_ID_PCM_ALAW,
    AV_CODEC_ID_PCM_S32LE,
    AV_CODEC_ID_PCM_S32BE,
    AV_CODEC_ID_PCM_U32LE,
    AV_CODEC_ID_PCM_U32BE,
    AV_CODEC_ID_PCM_S24LE,
    AV_CODEC_ID_PCM_S24BE,
    AV_CODEC_ID_PCM_U24LE,
    AV_CODEC_ID_PCM_U24BE,
    AV_CODEC_ID_PCM_S24DAUD,
    AV_CODEC_ID_PCM_ZORK,
    AV_CODEC_ID_PCM_S16LE_PLANAR,
    AV_CODEC_ID_PCM_DVD,
    AV_CODEC_ID_PCM_F32BE,
    AV_CODEC_ID_PCM_F32LE,
    AV_CODEC_ID_PCM_F64BE,
    AV_CODEC_ID_PCM_F64LE,
    AV_CODEC_ID_PCM_BLURAY,
    AV_CODEC_ID_PCM_LXF,
    AV_CODEC_ID_S302M,
    AV_CODEC_ID_PCM_S8_PLANAR,
    AV_CODEC_ID_PCM_S24LE_PLANAR,
    AV_CODEC_ID_PCM_S32LE_PLANAR,
    AV_CODEC_ID_PCM_S16BE_PLANAR,
    /* new PCM "codecs" should be added right below this line starting with
     * an explicit value of for example 0x10800
     */

    /* various ADPCM codecs */
    AV_CODEC_ID_ADPCM_IMA_QT = 0x11000,
    AV_CODEC_ID_ADPCM_IMA_WAV,
    AV_CODEC_ID_ADPCM_IMA_DK3,
    AV_CODEC_ID_ADPCM_IMA_DK4,
    AV_CODEC_ID_ADPCM_IMA_WS,
    AV_CODEC_ID_ADPCM_IMA_SMJPEG,
    AV_CODEC_ID_ADPCM_MS,
    AV_CODEC_ID_ADPCM_4XM,
    AV_CODEC_ID_ADPCM_XA,
    AV_CODEC_ID_ADPCM_ADX,
    AV_CODEC_ID_ADPCM_EA,
    AV_CODEC_ID_ADPCM_G726,
    AV_CODEC_ID_ADPCM_CT,
    AV_CODEC_ID_ADPCM_SWF,
    AV_CODEC_ID_ADPCM_YAMAHA,
    AV_CODEC_ID_ADPCM_SBPRO_4,
    AV_CODEC_ID_ADPCM_SBPRO_3,
    AV_CODEC_ID_ADPCM_SBPRO_2,
    AV_CODEC_ID_ADPCM_THP,
    AV_CODEC_ID_ADPCM_IMA_AMV,
    AV_CODEC_ID_ADPCM_EA_R1,
    AV_CODEC_ID_ADPCM_EA_R3,
    AV_CODEC_ID_ADPCM_EA_R2,
    AV_CODEC_ID_ADPCM_IMA_EA_SEAD,
    AV_CODEC_ID_ADPCM_IMA_EA_EACS,
    AV_CODEC_ID_ADPCM_EA_XAS,
    AV_CODEC_ID_ADPCM_EA_MAXIS_XA,
    AV_CODEC_ID_ADPCM_IMA_ISS,
    AV_CODEC_ID_ADPCM_G722,
    AV_CODEC_ID_ADPCM_IMA_APC,
    AV_CODEC_ID_ADPCM_VIMA,
#ifdef FF_API_VIMA_DECODER
    AV_CODEC_ID_VIMA = AV_CODEC_ID_ADPCM_VIMA,
#endif

    AV_CODEC_ID_ADPCM_AFC = 0x11800,
    AV_CODEC_ID_ADPCM_IMA_OKI,
    AV_CODEC_ID_ADPCM_DTK,
    AV_CODEC_ID_ADPCM_IMA_RAD,
    AV_CODEC_ID_ADPCM_G726LE,
    AV_CODEC_ID_ADPCM_THP_LE,
    AV_CODEC_ID_ADPCM_PSX,
    AV_CODEC_ID_ADPCM_AICA,

    /* AMR */
    AV_CODEC_ID_AMR_NB = 0x12000,
    AV_CODEC_ID_AMR_WB,

    /* RealAudio codecs*/
    AV_CODEC_ID_RA_144 = 0x13000,
    AV_CODEC_ID_RA_288,

    /* various DPCM codecs */
    AV_CODEC_ID_ROQ_DPCM = 0x14000,
    AV_CODEC_ID_INTERPLAY_DPCM,
    AV_CODEC_ID_XAN_DPCM,
    AV_CODEC_ID_SOL_DPCM,

    AV_CODEC_ID_SDX2_DPCM = 0x14800,

    /* audio codecs */
    AV_CODEC_ID_MP2 = 0x15000,
    AV_CODEC_ID_MP3, ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
    AV_CODEC_ID_AAC,
    AV_CODEC_ID_AC3,
    AV_CODEC_ID_DTS,
    AV_CODEC_ID_VORBIS,
    AV_CODEC_ID_DVAUDIO,
    AV_CODEC_ID_WMAV1,
    AV_CODEC_ID_WMAV2,
    AV_CODEC_ID_MACE3,
    AV_CODEC_ID_MACE6,
    AV_CODEC_ID_VMDAUDIO,
    AV_CODEC_ID_FLAC,
    AV_CODEC_ID_MP3ADU,
    AV_CODEC_ID_MP3ON4,
    AV_CODEC_ID_SHORTEN,
    AV_CODEC_ID_ALAC,
    AV_CODEC_ID_WESTWOOD_SND1,
    AV_CODEC_ID_GSM, ///< as in Berlin toast format
    AV_CODEC_ID_QDM2,
    AV_CODEC_ID_COOK,
    AV_CODEC_ID_TRUESPEECH,
    AV_CODEC_ID_TTA,
    AV_CODEC_ID_SMACKAUDIO,
    AV_CODEC_ID_QCELP,
    AV_CODEC_ID_WAVPACK,
    AV_CODEC_ID_DSICINAUDIO,
    AV_CODEC_ID_IMC,
    AV_CODEC_ID_MUSEPACK7,
    AV_CODEC_ID_MLP,
    AV_CODEC_ID_GSM_MS, /* as found in WAV */
    AV_CODEC_ID_ATRAC3,
#ifdef FF_API_VOXWARE
    AV_CODEC_ID_VOXWARE,
#endif
    AV_CODEC_ID_APE,
    AV_CODEC_ID_NELLYMOSER,
    AV_CODEC_ID_MUSEPACK8,
    AV_CODEC_ID_SPEEX,
    AV_CODEC_ID_WMAVOICE,
    AV_CODEC_ID_WMAPRO,
    AV_CODEC_ID_WMALOSSLESS,
    AV_CODEC_ID_ATRAC3P,
    AV_CODEC_ID_EAC3,
    AV_CODEC_ID_SIPR,
    AV_CODEC_ID_MP1,
    AV_CODEC_ID_TWINVQ,
    AV_CODEC_ID_TRUEHD,
    AV_CODEC_ID_MP4ALS,
    AV_CODEC_ID_ATRAC1,
    AV_CODEC_ID_BINKAUDIO_RDFT,
    AV_CODEC_ID_BINKAUDIO_DCT,
    AV_CODEC_ID_AAC_LATM,
    AV_CODEC_ID_QDMC,
    AV_CODEC_ID_CELT,
    AV_CODEC_ID_G723_1,
    AV_CODEC_ID_G729,
    AV_CODEC_ID_8SVX_EXP,
    AV_CODEC_ID_8SVX_FIB,
    AV_CODEC_ID_BMV_AUDIO,
    AV_CODEC_ID_RALF,
    AV_CODEC_ID_IAC,
    AV_CODEC_ID_ILBC,
    AV_CODEC_ID_OPUS,
    AV_CODEC_ID_COMFORT_NOISE,
    AV_CODEC_ID_TAK,
    AV_CODEC_ID_METASOUND,
    AV_CODEC_ID_PAF_AUDIO,
    AV_CODEC_ID_ON2AVC,
    AV_CODEC_ID_DSS_SP,

    AV_CODEC_ID_FFWAVESYNTH = 0x15800,
    AV_CODEC_ID_SONIC,
    AV_CODEC_ID_SONIC_LS,
    AV_CODEC_ID_EVRC,
    AV_CODEC_ID_SMV,
    AV_CODEC_ID_DSD_LSBF,
    AV_CODEC_ID_DSD_MSBF,
    AV_CODEC_ID_DSD_LSBF_PLANAR,
    AV_CODEC_ID_DSD_MSBF_PLANAR,
    AV_CODEC_ID_4GV,
    AV_CODEC_ID_XMA1,
    AV_CODEC_ID_XMA2,

    /* subtitle codecs */
    AV_CODEC_ID_FIRST_SUBTITLE = 0x17000,          ///< A dummy ID pointing at the start of subtitle codecs.
    AV_CODEC_ID_DVD_SUBTITLE = 0x17000,
    AV_CODEC_ID_DVB_SUBTITLE,
    AV_CODEC_ID_TEXT,  ///< raw UTF-8 text
    AV_CODEC_ID_XSUB,
    AV_CODEC_ID_SSA,
    AV_CODEC_ID_MOV_TEXT,
    AV_CODEC_ID_HDMV_PGS_SUBTITLE,
    AV_CODEC_ID_DVB_TELETEXT,
    AV_CODEC_ID_SRT,

    AV_CODEC_ID_MICRODVD   = 0x17800,
    AV_CODEC_ID_EIA_608,
    AV_CODEC_ID_JACOSUB,
    AV_CODEC_ID_SAMI,
    AV_CODEC_ID_REALTEXT,
    AV_CODEC_ID_STL,
    AV_CODEC_ID_SUBVIEWER1,
    AV_CODEC_ID_SUBVIEWER,
    AV_CODEC_ID_SUBRIP,
    AV_CODEC_ID_WEBVTT,
    AV_CODEC_ID_MPL2,
    AV_CODEC_ID_VPLAYER,
    AV_CODEC_ID_PJS,
    AV_CODEC_ID_ASS,
    AV_CODEC_ID_HDMV_TEXT_SUBTITLE,

    /* other specific kind of codecs (generally used for attachments) */
    AV_CODEC_ID_FIRST_UNKNOWN = 0x18000,           ///< A dummy ID pointing at the start of various fake codecs.
    AV_CODEC_ID_TTF = 0x18000,

    AV_CODEC_ID_BINTEXT    = 0x18800,
    AV_CODEC_ID_XBIN,
    AV_CODEC_ID_IDF,
    AV_CODEC_ID_OTF,
    AV_CODEC_ID_SMPTE_KLV,
    AV_CODEC_ID_DVD_NAV,
    AV_CODEC_ID_TIMED_ID3,
    AV_CODEC_ID_BIN_DATA,

    AV_CODEC_ID_PROBE = 0x19000, ///< codec_id is not known (like AV_CODEC_ID_NONE) but lavf should attempt to identify it

    AV_CODEC_ID_MPEG2TS = 0x20000, /**< _FAKE_ codec to indicate a raw MPEG-2 TS
                                * stream (only used by libavformat) */
    AV_CODEC_ID_MPEG4SYSTEMS = 0x20001, /**< _FAKE_ codec to indicate a MPEG-4 Systems
                                * stream (only used by libavformat) */
    AV_CODEC_ID_FFMETADATA = 0x21000,   ///< Dummy codec for streams containing only metadata information.
    AV_CODEC_ID_WRAPPED_AVFRAME = 0x21001, ///< Passthrough codec, AVFrames wrapped in AVPacket
} AVCodecID_E;

enum AudioObjectType {
    AOT_NULL,
                               // Support?                Name
    AOT_AAC_MAIN,              ///< Y                       Main
    AOT_AAC_LC,                ///< Y                       Low Complexity
    AOT_AAC_SSR,               ///< N (code in SoC repo)    Scalable Sample Rate
    AOT_AAC_LTP,               ///< Y                       Long Term Prediction
    AOT_SBR,                   ///< Y                       Spectral Band Replication
    AOT_AAC_SCALABLE,          ///< N                       Scalable
    AOT_TWINVQ,                ///< N                       Twin Vector Quantizer
    AOT_CELP,                  ///< N                       Code Excited Linear Prediction
    AOT_HVXC,                  ///< N                       Harmonic Vector eXcitation Coding
    AOT_TTSI             = 12, ///< N                       Text-To-Speech Interface
    AOT_MAINSYNTH,             ///< N                       Main Synthesis
    AOT_WAVESYNTH,             ///< N                       Wavetable Synthesis
    AOT_MIDI,                  ///< N                       General MIDI
    AOT_SAFX,                  ///< N                       Algorithmic Synthesis and Audio Effects
    AOT_ER_AAC_LC,             ///< N                       Error Resilient Low Complexity
    AOT_ER_AAC_LTP       = 19, ///< N                       Error Resilient Long Term Prediction
    AOT_ER_AAC_SCALABLE,       ///< N                       Error Resilient Scalable
    AOT_ER_TWINVQ,             ///< N                       Error Resilient Twin Vector Quantizer
    AOT_ER_BSAC,               ///< N                       Error Resilient Bit-Sliced Arithmetic Coding
    AOT_ER_AAC_LD,             ///< N                       Error Resilient Low Delay
    AOT_ER_CELP,               ///< N                       Error Resilient Code Excited Linear Prediction
    AOT_ER_HVXC,               ///< N                       Error Resilient Harmonic Vector eXcitation Coding
    AOT_ER_HILN,               ///< N                       Error Resilient Harmonic and Individual Lines plus Noise
    AOT_ER_PARAM,              ///< N                       Error Resilient Parametric
    AOT_SSC,                   ///< N                       SinuSoidal Coding
    AOT_PS,                    ///< N                       Parametric Stereo
    AOT_SURROUND,              ///< N                       MPEG Surround
    AOT_ESCAPE,                ///< Y                       Escape Value
    AOT_L1,                    ///< Y                       Layer 1
    AOT_L2,                    ///< Y                       Layer 2
    AOT_L3,                    ///< Y                       Layer 3
    AOT_DST,                   ///< N                       Direct Stream Transfer
    AOT_ALS,                   ///< Y                       Audio LosslesS
    AOT_SLS,                   ///< N                       Scalable LosslesS
    AOT_SLS_NON_CORE,          ///< N                       Scalable LosslesS (non core)
    AOT_ER_AAC_ELD,            ///< N                       Error Resilient Enhanced Low Delay
    AOT_SMR_SIMPLE,            ///< N                       Symbolic Music Representation Simple
    AOT_SMR_MAIN,              ///< N                       Symbolic Music Representation Main
    AOT_USAC_NOSBR,            ///< N                       Unified Speech and Audio Coding (no SBR)
    AOT_SAOC,                  ///< N                       Spatial Audio Object Coding
    AOT_LD_SURROUND,           ///< N                       Low Delay MPEG Surround
    AOT_USAC,                  ///< N                       Unified Speech and Audio Coding
};

typedef struct _AVCodecTag {
    AVCodecID_E id;
    unsigned int tag;
} AVCodecTag;

typedef struct _CodecMime {
    char str[32];
    AVCodecID_E id;
} CodecMime;

typedef struct _AVRational {
    int num;
    int den;
} AVRational;

enum AVDiscard {
    AVDISCARD_NONE    =-16, 
    AVDISCARD_DEFAULT =  0, 
    AVDISCARD_NONREF  =  8, 
    AVDISCARD_BIDIR   = 16,
    AVDISCARD_NONINTRA= 24,
    AVDISCARD_NONKEY  = 32,
    AVDISCARD_ALL     = 48,
};

enum AVRounding {
    AV_ROUND_ZERO     = 0,
    AV_ROUND_INF      = 1,
    AV_ROUND_DOWN     = 2,
    AV_ROUND_UP       = 3,
    AV_ROUND_NEAR_INF = 5,
    AV_ROUND_PASS_MINMAX = 8192,
};

#define AV_DISPOSITION_DEFAULT           0x0001
#define AV_DISPOSITION_DUB               0x0002
#define AV_DISPOSITION_ORIGINAL          0x0004
#define AV_DISPOSITION_COMMENT           0x0008
#define AV_DISPOSITION_LYRICS            0x0010
#define AV_DISPOSITION_KARAOKE           0x0020
#define AV_DISPOSITION_FORCED            0x0040
#define AV_DISPOSITION_HEARING_IMPAIRED  0x0080
#define AV_DISPOSITION_VISUAL_IMPAIRED   0x0100
#define AV_DISPOSITION_CLEAN_EFFECTS     0x0200
#define AV_DISPOSITION_ATTACHED_PIC      0x0400


typedef struct _AVIndexEntry {
    int64_t pos;
    int64_t timestamp;
#define AVINDEX_KEYFRAME 0x0001
    int flags:2;
    int size:30; 
    int min_distance;  
} AVIndexEntry;

enum AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1, 
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_DATA,        
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,
    AVMEDIA_TYPE_NB
};

enum AVAudioServiceType {
    AV_AUDIO_SERVICE_TYPE_MAIN              = 0,
    AV_AUDIO_SERVICE_TYPE_EFFECTS           = 1,
    AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED = 2,
    AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED  = 3,
    AV_AUDIO_SERVICE_TYPE_DIALOGUE          = 4,
    AV_AUDIO_SERVICE_TYPE_COMMENTARY        = 5,
    AV_AUDIO_SERVICE_TYPE_EMERGENCY         = 6,
    AV_AUDIO_SERVICE_TYPE_VOICE_OVER        = 7,
    AV_AUDIO_SERVICE_TYPE_KARAOKE           = 8,
    AV_AUDIO_SERVICE_TYPE_NB                   , ///< Not part of ABI
};

enum AVPacketSideDataType {
    AV_PKT_DATA_PALETTE,
    AV_PKT_DATA_NEW_EXTRADATA,
    AV_PKT_DATA_PARAM_CHANGE,
    AV_PKT_DATA_H263_MB_INFO,
    AV_PKT_DATA_REPLAYGAIN,
    AV_PKT_DATA_DISPLAYMATRIX,
    AV_PKT_DATA_STEREO3D,
    AV_PKT_DATA_AUDIO_SERVICE_TYPE,
    AV_PKT_DATA_QUALITY_STATS,
    AV_PKT_DATA_SKIP_SAMPLES=70,
    AV_PKT_DATA_JP_DUALMONO,
    AV_PKT_DATA_STRINGS_METADATA,
    AV_PKT_DATA_SUBTITLE_POSITION,
    AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL,
    AV_PKT_DATA_WEBVTT_IDENTIFIER,
    AV_PKT_DATA_WEBVTT_SETTINGS,
    AV_PKT_DATA_METADATA_UPDATE,
};

typedef struct _MPEG4AudioConfig {
    int object_type;
    int sampling_index;
    int sample_rate;
    int chan_config;
    int sbr;
    int ext_object_type;
    int ext_sampling_index;
    int ext_sample_rate;
    int ext_chan_config;
    int channels;
    int ps; 
    int frame_length_short;
} MPEG4AudioConfig;

typedef struct AVProfile {
    int profile;
    const char *name; 
} AVProfile;

typedef struct AVCodec {
    const char *name;
    const char *long_name;
    enum AVMediaType type;
    AVCodecID_E id;
    int capabilities;
    const uint64_t *channel_layouts;
    const AVProfile *profiles;
    int priv_data_size;
    struct AVCodec *next;
} AVCodec;

typedef struct __AVCodecDescriptor {
    AVCodecID_E     id;
    enum AVMediaType type;
    const char      *name;
    const char *long_name;
    int             props;
    const char *const *mime_types;
    const struct AVProfile *profiles;
} AVCodecDescriptor;

#define AV_CODEC_PROP_LOSSY         (1 << 1)
#define AV_CODEC_PROP_LOSSLESS      (1 << 2)

#define AV_CODEC_FLAG_GLOBAL_HEADER   (1 << 22)
#define AV_CODEC_FLAG2_LOCAL_HEADER   (1 <<  3)

typedef struct _AVCodecContext {
    enum AVMediaType codec_type;
    const struct AVCodec *codec;
    AVCodecID_E codec_id; 
    int sample_rate;
    int channels;   
    int block_align;
    int has_b_frames;
    uint64_t channel_layout;
    uint64_t request_channel_layout;
    AVRational pkt_timebase;
    enum AVAudioServiceType audio_service_type;
    int64_t bit_rate;
    int64_t rc_max_rate;
    int bits_per_coded_sample;
    int frame_size;
    int flags;
    int flags2;
    uint8_t *extradata;
    int extradata_size;
    unsigned int codec_tag;
    AVRational time_base;
    int delay;
    const AVCodecDescriptor *codec_descriptor;
     int profile;
#define DMX_PROFILE_UNKNOWN -99
#define DMX_PROFILE_RESERVED -100

#define DMX_PROFILE_AAC_MAIN 0
#define DMX_PROFILE_AAC_LOW  1
#define DMX_PROFILE_AAC_SSR  2
#define DMX_PROFILE_AAC_LTP  3
#define DMX_PROFILE_AAC_HE   4
#define DMX_PROFILE_AAC_HE_V2 28
#define DMX_PROFILE_AAC_LD   22
#define DMX_PROFILE_AAC_ELD  38
#define DMX_PROFILE_MPEG2_AAC_LOW 128
#define DMX_PROFILE_MPEG2_AAC_HE  131

#define DMX_PROFILE_DTS         20
#define DMX_PROFILE_DTS_ES      30
#define DMX_PROFILE_DTS_96_24   40
#define DMX_PROFILE_DTS_HD_HRA  50
#define DMX_PROFILE_DTS_HD_MA   60
#define DMX_PROFILE_DTS_EXPRESS 70
} AVCodecContext;

#define PROBE_BUF_MIN                2048
#define PROBE_BUF_MAX                (1 << 20)
#define MAX_PROBE_PACKETS            2500
#define AVPROBE_SCORE_RETRY          (AVPROBE_SCORE_MAX/4)
#define AVPROBE_SCORE_STREAM_RETRY   (AVPROBE_SCORE_MAX/4-1)

#define AVPROBE_SCORE_EXTENSION      50
#define AVPROBE_SCORE_MIME           75
#define AVPROBE_SCORE_MAX            100
#define AVPROBE_PADDING_SIZE         32

typedef struct _AVProbeData {
    const char *filename;
    unsigned char *buf;
    int buf_size; 
    const char *mime_type;
} AVProbeData;

typedef struct _AVDictionaryEntry {
    char *key;
    char *value;
} AVDictionaryEntry;

typedef struct _AVDictionary {
    int count;
    AVDictionaryEntry *elems;
} AVDictionary;

typedef enum __AVStreamParseType {
    AVSTREAM_PARSE_NONE,
    AVSTREAM_PARSE_FULL,    
    AVSTREAM_PARSE_HEADERS,
    AVSTREAM_PARSE_TIMESTAMPS,
    AVSTREAM_PARSE_FULL_ONCE,
    AVSTREAM_PARSE_FULL_RAW=MKTAG(0,'R','A','W'),
} AVStreamParseType;

typedef struct AVCodecParserContext {
    void *priv_data;
    struct AVCodecParser *parser;
    int64_t frame_offset; /* offset of the current frame */
    int64_t cur_offset; /* current offset
                           (incremented by each av_parser_parse()) */
    int64_t next_frame_offset; /* offset of the next frame */
    int64_t pts;
    int64_t dts;
    /* private data */
    int64_t last_pts;
    int64_t last_dts;
    int fetch_timestamp;

#define AV_PARSER_PTS_NB 4
    int cur_frame_start_index;
    int64_t cur_frame_offset[AV_PARSER_PTS_NB];
    int64_t cur_frame_pts[AV_PARSER_PTS_NB];
    int64_t cur_frame_dts[AV_PARSER_PTS_NB];

    int flags;
#define PARSER_FLAG_COMPLETE_FRAMES           0x0001
#define PARSER_FLAG_ONCE                      0x0002
/// Set if the parser has a valid file offset
#define PARSER_FLAG_FETCHED_OFFSET            0x0004
#define PARSER_FLAG_USE_CODEC_TS              0x1000

    int64_t offset;      ///< byte offset from starting packet start
    int64_t cur_frame_end[AV_PARSER_PTS_NB];

    // Timestamp generation support:
    /**
     * Synchronization point for start of timestamp generation.
     *
     * Set to >0 for sync point, 0 for no sync point and <0 for undefined
     * (default).
     *
     * For example, this corresponds to presence of H.264 buffering period
     * SEI message.
     */
    int dts_sync_point;

    /**
     * Offset of the current timestamp against last timestamp sync point in
     * units of AVCodecContext.time_base.
     *
     * Set to INT_MIN when dts_sync_point unused. Otherwise, it must
     * contain a valid timestamp offset.
     *
     * Note that the timestamp of sync point has usually a nonzero
     * dts_ref_dts_delta, which refers to the previous sync point. Offset of
     * the next frame after timestamp sync point will be usually 1.
     *
     * For example, this corresponds to H.264 cpb_removal_delay.
     */
    int dts_ref_dts_delta;

    /**
     * Presentation delay of current frame in units of AVCodecContext.time_base.
     *
     * Set to INT_MIN when dts_sync_point unused. Otherwise, it must
     * contain valid non-negative timestamp delta (presentation time of a frame
     * must not lie in the past).
     *
     * This delay represents the difference between decoding and presentation
     * time of the frame.
     *
     * For example, this corresponds to H.264 dpb_output_delay.
     */
    int pts_dts_delta;

    /**
     * Position of the packet in file.
     *
     * Analogous to cur_frame_pts/dts
     */
    int64_t cur_frame_pos[AV_PARSER_PTS_NB];

    /**
     * Byte position of currently parsed frame in stream.
     */
    int64_t pos;

    /**
     * Previous frame byte position.
     */
    int64_t last_pos;

    /**
     * Duration of the current frame.
     * For audio, this is in units of 1 / AVCodecContext.sample_rate.
     * For all other types, this is in units of AVCodecContext.time_base.
     */
    int duration;

    /**
     * The format of the coded data, corresponds to enum AVPixelFormat for video
     * and for enum AVSampleFormat for audio.
     *
     * Note that a decoder can have considerable freedom in how exactly it
     * decodes the data, so the format reported here might be different from the
     * one returned by a decoder.
     */
    int format;
} AVCodecParserContext;

#define AV_PTS_WRAP_IGNORE       0 
#define AV_PTS_WRAP_ADD_OFFSET   1 
#define AV_PTS_WRAP_SUB_OFFSET  -1

typedef struct __AVStream {
    int index; 
    int id;
    AVCodecContext *codec;
    AVProbeData probe_data;
    void *priv_data;
    AVRational time_base;
    int64_t start_time;
    int64_t duration;
    int64_t nb_frames; 
    int64_t first_dts;
    int64_t cur_dts;
    int pts_wrap_bits;
    int disposition;
    AVStreamParseType need_parsing;
    AVCodecParserContext *parser;
    int request_probe;
    int64_t pts_wrap_reference;
    int pts_wrap_behavior;
    int update_initial_durations_done;
    int stream_identifier;
    enum AVDiscard discard;
    AVDictionary *metadata;
    int skip_samples;
    int64_t start_skip_samples;
    int64_t first_discard_sample;
    int64_t last_discard_sample;
    AVIndexEntry *index_entries;
    int nb_index_entries;
    unsigned int index_entries_allocated_size;
    int probe_packets;
    int codec_info_nb_frames;
    int event_flags;
#define AVSTREAM_EVENT_FLAG_METADATA_UPDATED 0x0001 ///< The call resulted in updated metadata.
    
} AVStream;

#define AV_PKT_FLAG_KEY     0x0001 ///< The packet contains a keyframe
#define AV_PKT_FLAG_CORRUPT 0x0002 ///< The packet content is corrupted

typedef struct _AVPacket {
    int64_t pts;
    int64_t dts;
    int64_t pos; 
    uint8_t *rptr;
    uint8_t *data;
    int   size;
    int   stream_index;
    int   flags;
    int64_t duration;
} AVPacket;

typedef struct _AVPacketList {
    AVPacket pkt;
    struct AVPacketList *next;
} AVPacketList;

typedef struct _AVFormatInternal {
    int nb_interleaved_streams;

    struct AVPacketList *packet_buffer;
    struct AVPacketList *packet_buffer_end;

    int64_t data_offset;

    struct AVPacketList *raw_packet_buffer;
    struct AVPacketList *raw_packet_buffer_end;

    struct AVPacketList *parse_queue;
    struct AVPacketList *parse_queue_end;

#define RAW_PACKET_BUFFER_SIZE 25000
    int raw_packet_buffer_remaining_size;

    int64_t offset;

    AVRational offset_timebase;

    int inject_global_side_data;

    int avoid_negative_ts_use_pts;

    int header_written;
} AVFormatInternal;

typedef struct AVProgram {
    int            id;
    int            flags;
    enum AVDiscard discard;        ///< selects which program to discard and which to feed to the caller
    unsigned int   *stream_index;
    unsigned int   nb_stream_indexes;
    AVDictionary   *metadata;

    int            program_num;
    int            pmt_pid;
    int            pcr_pid;

    /*****************************************************************
     * All fields below this line are not part of the public API. They
     * may not be used outside of libavformat and can be changed and
     * removed at will.
     * New public fields should be added right above.
     *****************************************************************
     */
    int64_t        start_time;
    int64_t        end_time;

    int64_t        pts_wrap_reference;    ///< reference dts for wrap detection
    int            pts_wrap_behavior;         ///< behavior on wrap detection
} AVProgram;


typedef struct AVChapter {
    int id;              
    AVRational time_base; 
    int64_t start, end; 
    AVDictionary *metadata;
} AVChapter;

#define AVFMT_NOFILE                      0x0001
#define AVFMT_SHOW_IDS                    0x0002

#define AVFMT_GLOBALHEADER                0x0040 
#define AVFMT_NOTIMESTAMPS                0x0080

#define AVFMT_GENERIC_INDEX               0x0100
#define AVFMT_TS_DISCONT                  0x0200

#define AVFMT_EVENT_FLAG_METADATA_UPDATED 0x0001
#define AVFMT_NO_BYTE_SEEK                0x8000

#define AVFMTCTX_NOHEADER                 0x0001

typedef struct _AVFormatContext AVFormatContext;

typedef struct AVInputFormat {
    const char *name;
    const char *long_name;
    int flags;
    const char *extensions;
    const char *mime_type;
    const struct AVCodecTag * const *codec_tag;
    struct AVInputFormat *next;
    int raw_codec_id;
    int priv_data_size;
    int (*read_probe)(AVProbeData *);
    int (*read_header)(AVFormatContext *);
    int (*read_packet)(AVFormatContext *, AVPacket *pkt, int which);
    int (*read_close)(AVFormatContext *);
    int (*read_seek)(AVFormatContext *,
                     int stream_index, int64_t timestamp, int flags);
    int (*read_seek2)(AVFormatContext *s, int stream_index,
                      int64_t min_ts, int64_t ts, int64_t max_ts, int flags);

    int64_t (*read_timestamp)(AVFormatContext *, int stream_index,
                              int64_t *pos, int64_t post_limit);
} AVInputFormat;

typedef struct _AVIOContext {
    unsigned char *buffer; 
    int buffer_size;      
    unsigned char *buf_ptr;
    unsigned char *buf_end;
    void *opaque; 
    int (*read_packet)(void *opaque, uint8_t *buf, int buf_size);
    int (*write_packet)(void *opaque, uint8_t *buf, int buf_size);
    int64_t (*seek)(void *opaque, int64_t offset, int whence);
    int64_t pos; 
    int must_flush;
    int eof_reached;
    int write_flag;
    int max_packet_size;
    int error; 
    int (*read_pause)(void *opaque, int pause);
    int64_t (*read_seek)(void *opaque, int stream_index,
                         int64_t timestamp, int flags);
    unsigned long checksum;
    unsigned char *checksum_ptr;
    unsigned long (*update_checksum)(unsigned long checksum,
                                     const uint8_t *buf,
                                     unsigned int size);

    int seekable;
    int64_t maxsize;
    int direct;
    int64_t bytes_read;
    int seek_count;
    int writeout_count;
    int orig_buffer_size;
    int short_seek_threshold;
} AVIOContext;

struct _AVFormatContext {
    void *priv_data;
    AVIOContext *pb;
    int          which;
    int          ctx_flags;
    unsigned int nb_streams;
    AVStream **streams;
    unsigned int nb_chapters;
    AVChapter **chapters;
    char filename[1024];
    int event_flags;
    int flags;
#define AVFMT_FLAG_GENPTS       0x0001 
#define AVFMT_FLAG_IGNIDX       0x0002
#define AVFMT_FLAG_NONBLOCK     0x0004
#define AVFMT_FLAG_IGNDTS       0x0008
#define AVFMT_FLAG_NOFILLIN     0x0010
#define AVFMT_FLAG_NOPARSE      0x0020
#define AVFMT_FLAG_NOBUFFER     0x0040
#define AVFMT_FLAG_CUSTOM_IO    0x0080
#define AVFMT_FLAG_DISCARD_CORRUPT  0x0100
#define AVFMT_FLAG_FLUSH_PACKETS    0x0200
#define AVFMT_FLAG_BITEXACT         0x0400
#define AVFMT_NOBINSEARCH           0x2000
#define AVFMT_NOGENSEARCH           0x04000
#define AVFMT_FLAG_MP4A_LATM        0x8000
#define AVFMT_FLAG_SORT_DTS        0x10000
#define AVFMT_FLAG_PRIV_OPT        0x20000
#define AVFMT_FLAG_KEEP_SIDE_DATA  0x40000
#define AVFMT_FLAG_FAST_SEEK       0x80000

    int64_t probesize;
    int64_t duration;
    int64_t start_time;
    int64_t max_analyze_duration;
    int64_t bit_rate;
    unsigned int packet_size;

    const uint8_t *key;
    int keylen;

    unsigned int nb_programs;
    AVProgram **programs;
    AVCodecID_E video_codec_id;
    AVCodecID_E audio_codec_id;
    AVCodecID_E subtitle_codec_id;
    int  probe_score;
    int  ts_id;
    unsigned int max_index_size;
    AVDictionary *metadata;
    MPEG4AudioConfig cfg;
    AVInputFormat *iformat;
    AVFormatInternal *internal;
    int io_repositioned;
#if 0
    int (*open_cb)(struct AVFormatContext *s, AVIOContext **p,
                   const char *url, int flags,
                   const AVIOInterruptCB *int_cb, AVDictionary **options);
#endif
};

typedef struct AVCodecParser {
    int codec_ids[5]; /* several codec IDs are permitted */
    int priv_data_size;
    int (*parser_init)(AVCodecParserContext *s);
    /* This callback never returns an error, a negative value means that
     * the frame start was in a previous packet. */
    int (*parser_parse)(AVCodecParserContext *s,
                        AVCodecContext *avctx,
                        const uint8_t **poutbuf, int *poutbuf_size,
                        const uint8_t *buf, int buf_size);
    void (*parser_close)(AVCodecParserContext *s);
    int (*split)(AVCodecContext *avctx, const uint8_t *buf, int buf_size);
    struct AVCodecParser *next;
} AVCodecParser;

AVCodecParser *av_parser_next(const AVCodecParser *c);

void av_register_codec_parser(AVCodecParser *parser);
AVCodecParserContext *av_parser_init(int codec_id);

/**
 * Parse a packet.
 *
 * @param s             parser context.
 * @param avctx         codec context.
 * @param poutbuf       set to pointer to parsed buffer or NULL if not yet finished.
 * @param poutbuf_size  set to size of parsed buffer or zero if not yet finished.
 * @param buf           input buffer.
 * @param buf_size      input length, to signal EOF, this should be 0 (so that the last frame can be output).
 * @param pts           input presentation timestamp.
 * @param dts           input decoding timestamp.
 * @param pos           input byte position in stream.
 * @return the number of bytes of the input bitstream used.
 *
 * Example:
 * @code
 *   while(in_len){
 *       len = av_parser_parse2(myparser, AVCodecContext, &data, &size,
 *                                        in_data, in_len,
 *                                        pts, dts, pos);
 *       in_data += len;
 *       in_len  -= len;
 *
 *       if(size)
 *          decode_frame(data, size);
 *   }
 * @endcode
 */
int av_parser_parse2(AVCodecParserContext *s,
                     AVCodecContext *avctx,
                     uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size,
                     int64_t pts, int64_t dts,
                     int64_t pos);

/**
 * @return 0 if the output buffer is a subset of the input, 1 if it is allocated and must be freed
 * @deprecated use AVBitStreamFilter
 */
int av_parser_change(AVCodecParserContext *s,
                     AVCodecContext *avctx,
                     uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size, int keyframe);
void av_parser_close(AVCodecParserContext *s);

const AVCodecDescriptor *avcodec_descriptor_get(AVCodecID_E id);;
const AVCodecDescriptor *avcodec_descriptor_next(const AVCodecDescriptor *prev);
const AVCodecDescriptor *avcodec_descriptor_get_by_name(const char *name);

#define MAKE_ACCESSORS(str, name, type, field) \
    type av_##name##_get_##field(const str *s) { return s->field; } \
    void av_##name##_set_##field(str *s, type v) { s->field = v; }

#endif /* TYPES_H */
