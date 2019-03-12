/*
 * sladsp_ae.h
 */
#ifndef __SLADSP_AE_H__
#define __SLADSP_AE_H__

/*
 * Post Proc Interface
 *
 * list   -> AUDPROC_LIST
 * module -> AUDPROC_ID
 * 
 * example: 
 * 	swa_audio_audproc_load(AUDPROC_LIST_DEC, AUDPROC_EQ);
 * 	this will load digital equalizer in the list dec and
 * 	only decoded data will be processed
 *
 * procedure:
 * 	audproc_load -> audproc_eq   -> audproc_set -> audproc_unload	EQ
 * 	audproc_load -> audproc_echo -> audproc_set -> audproc_unload	ECHO
 * 	audproc_load -> audproc_pts  -> audproc_set -> audproc_unload	PTS
 * 	audproc_load -> audproc_revb -> audproc_set -> audproc_unload	REVB
 * 	audproc_load -> audproc_btr  -> audproc_set -> audproc_unload	BTR
 * 	audproc_load -> audproc_vol  -> audproc_set -> audproc_unload	VOL
 *
 * 	audproc_load ->              -> audproc_set -> audproc_unload	VBASS		\
 * 	audproc_load ->              -> audproc_set -> audproc_unload	DIALENH		 \ choose one
 * 	audproc_load ->              -> audproc_set -> audproc_unload	SURROUND	 / of them
 * 	audproc_load ->              -> audproc_set -> audproc_unload	3D			/
 */

typedef enum {
	AUDPROC_CMD_LOAD,
	AUDPROC_CMD_UNLOAD,
	AUDPROC_CMD_SET,
	AUDPROC_CMD_ON,
	AUDPROC_CMD_OFF
}AUDPROC_CMD;

typedef enum {
	AUDPROC_LIST_DEC,
	AUDPROC_LIST_ADC0,
	AUDPROC_LIST_ADC1,
	AUDPROC_LIST_ADC2,
	AUDPROC_LIST_MIX,
	AUDPROC_LIST_MAX
}AUDPROC_LIST;

typedef enum {
	AUDPROC_NULL = -1,
	AUDPROC_MIX,         // Up or Down Mixing
	AUDPROC_VBASS,       // Virtual Bass 
	AUDPROC_DIALENH,     // Dialog Enhancement
	AUDPROC_3D,          // 3D Audio
	AUDPROC_SURROUND,    // Virtual Surround
    AUDPROC_STEREO2MONO, // Stereo to Mono
    AUDPROC_MONO2STEREO, // Mono to Stereo
	AUDPROC_RESAMPLE,    // Resample
	AUDPROC_EQ,          // Digital Equalizer 
	AUDPROC_LOUDCTL,     // Loudness Control
	AUDPROC_PTS,         // Pitch and/or Time Shift
	AUDPROC_VOLUMECTL,   // Volume Control
	AUDPROC_ALC,         // Level Control
	AUDPROC_AUTOMUTE,    // Auto Mute
	AUDPROC_REVERB,      // Reverbration
	AUDPROC_ECHO,        // Echo
	AUDPROC_BASSTREBLE,  // Bass and Treble 
	AUDPROC_COMPRESSOR,  // Dynamic Range Compressor
    AUDPROC_VOICECANCEL, // Voice Cancel
    AUDPROC_CUSTOM,      // Custom
    AUDPROC_SHOW_PS,     // Show Ps
    AUDPROC_SHOW_PEAK,   // Show Peak
    AUDPROC_MUTE_DECT,   // Mute Detection
	AUDPROC_VAD,         // Voice Activity Detection 
	AUDPROC_NS,          // Noise Suppression 
	AUDPROC_AGC,         // Automatic Gain Control
	AUDPROC_AEC,         // Acoustic Echo Control
	AUDPROC_AFC,         // Acoustic Feedback Control
	AUDPROC_SOSF,        // Second Order Sections Filter
    AUDPROC_DELAY,       // Delay
    AUDPROC_DIRECT_SOUND,// Direct Sound
    AUDPROC_NOISE_GATE,  // Noise Gate
    AUDPROC_ENERGY,      // Energy
	AUDPROC_NUMS
}AUDPROC_ID;

int swa_audio_audproc_load(AUDPROC_LIST list, AUDPROC_ID module);
int swa_audio_audproc_unload(AUDPROC_LIST list, AUDPROC_ID module);
//  swa_audio_audproc_#ae_name#(AUDPROC_LIST list, #ae_para#)
//  return value
//  if #ae_para# is reasonable  0
//  else                        -1
//
int swa_audio_audproc_set(AUDPROC_LIST list, AUDPROC_ID module);

int swa_audio_audproc_show(AUDPROC_LIST list);

/*
 * Volume Control
 */

#define VolCtrl_Max_Channel	6
#define VolCtrl_Max_DB		6
#define VolCtrl_Min_DB		-64
#define VolCtrl_Max_Linear	100
#define VolCtrl_Min_Linear	0

typedef enum {
	VOL_LINEAR  = 0,
	VOL_DB      = 1,
	VOL_MODE_MAX,
}ae_vol_mode;

typedef enum{
    SET_LIN_VOL = 1,
    SET_MIC_VOL,
    SET_DEC_VOL,
    SET_MIX_VOL,
    SET_ADC1_VOL,
    SET_ADC2_VOL,
}ae_vol_sel;

int swa_audio_set_vol(int name, int *vol);
int swa_audio_get_vol(int name);

int swa_audio_audproc_vol(AUDPROC_LIST list, int mode, int *vol);

/*
 * Vol Balance
 */
typedef struct{
	int on[5];         // 0: off, 1:on
	int percent[5];    // 0 ~ 100 (0% ~ 100%) 
}swa_ae_vol_balance_t;

int swa_audio_audproc_vol_balance(AUDPROC_LIST list, int onoff, int percent);

/*
 * Level Control
 */

int swa_audio_audproc_alc(AUDPROC_LIST list, int mode, int *vol);

/*
 * Equalizer
 */ 

typedef enum
{
    TYPE_PK = 0,  // peaking
    TYPE_AP1,     // single pole allpass
    TYPE_AP2,     // two pole allpass
    TYPE_BP,      // bandpass
    TYPE_LP,      // lowpass
    TYPE_HP,      // highpass
    TYPE_LS,      // low shelf
    TYPE_HS,      // high shelf
    TYPE_MAX
} filter_type;

typedef struct {
	int flt_id;   /* 1 ~ 7                          */
	int type;     /* TYPE_PK ~ TYPE_HS              */
	int on;       /* 0: off, 1: on                  */
	int gain;     /* -1200 ~ 1200 (-12db ~ 12db)    */
	int fc;       /* center frequence, 20 ~ 96000   */
	int q;        /* width 50 ~ 300                 */
	int ch;       /* 0 ~ 6                          */
}ae_eq_para;

int swa_audio_audproc_eq(AUDPROC_LIST list, ae_eq_para* config);
int swa_audio_audproc_eq_mode(AUDPROC_LIST list, ae_eq_para config[6]);

/* 
 *   Class:     [flt_id type    on      gain    fc      q  ]
 *
 * - standard:  [1,     0,      1,      0,      100,    100],     
 *              [2,     0,      1,      0,      300,    100],     
 *              [3,     0,      1,      0,      1000,   300],     
 *              [4,     0,      1,      0,      3000,   300],     
 *              [5,     0,      1,      0,      8000,   300]
 *
 * - classic:   [1,     0,      1,      0,      100,    100],
 *              [2,     0,      1,      -500,   300,    100],
 *              [3,     0,      1,      -1200,  1000,   300],
 *              [4,     0,      1,      -1000,  3000,   300],
 *              [5,     0,      1,      -500,   8000,   300]
 *
 * - jazz:      [1,     0,      1,      -1200,  100,    100], 
 *              [2,     0,      1,      -800,   300,    100],
 *              [3,     0,      1,      -140,   1000,   300],
 *              [4,     0,      1,      0,      3000,   300],
 *              [5,     0,      1,      -800,   8000,   300]
 *
 * - rock:      [1,     0,      1,      0,      100,    100],
 *              [2,     0,      1,      -400,   300,    100],
 *              [3,     0,      1,      -1200,  1000,   300],
 *              [4,     0,      1,      -1200,  3000,   300],
 *              [5,     0,      1,      -400,   8000,   300]
 *                                      
 * - pops:      [1,     0,      1,      -200,   100,    100],
 *              [2,     0,      1,      0,      300,    100],
 *              [3,     0,      1,      -1100,  1000,   300],
 *              [4,     0,      1,      -1200,  3000,   300],
 *              [5,     0,      1,      -1100,  8000,   300]
 *                                      
 * - ballad:    [1,     0,      1,      -1000,  100,    100],
 *              [2,     0,      1,      -800,   300,    100],
 *              [3,     0,      1,      0,      1000,   100],
 *              [4,     0,      1,      -800,   3000,   300],
 *              [5,     0,      1,      -1200,  8000,   300]
 *                                      
 * - dance:     [1,     0,      1,      0,      100,    100],
 *              [2,     0,      1,      -400,   300,    100],
 *              [3,     0,      1,      -1200,  1000,   300],
 *              [4,     0,      1,      -1000,  3000,   300],
 *              [5,     0,      1,      -800,   8000,   300]
 */

/*
 * Reverberance
 */

typedef enum {
	VERB_RESET,
	VERB_VOCAL_I,
	VERB_VOCAL_II,
	VERB_BATHROOM,
	VERB_SMALL_ROOM1,
	VERB_SMALL_ROOM2,
	VERB_MEDIUM_ROOM,
	VERB_LARGE_ROOM,
	VERB_CHURCH_HALL,
	VERB_SANCTUARY,
	VERB_TYPE_MAX,
} ae_reverb_type;

typedef struct ReverbParam1_ {
    int roomsize;       // 0 ~ 100 %
    int damp;           // 0 ~ 100 %
    int predelay;       // 0 ~ 50 ms
    int reverberance;   // 0 ~ 100 %
    int tone_low;       // 0 ~ 100 %
    int tone_high;      // 0 ~ 100 %
    int wet;            // -24 ~ 0 db
    int dry;            // -24 ~ 0 db
    int width;          // 0 ~ 100 %
} ae_reverb_para1;

typedef struct ReverbParam2_ {
    int delay;  //20 ~ 100 ms
    int xover;  //50 ~ 1000 hz
    int rtlow;  //1000 ~ 8000 ms
    int rtmid;  //1000 ~ 8000 ms
    int fdamp;  //1500 ~ 24000 hz
    int opmix;  //0 ~ 100 %
} ae_reverb_para2;

int swa_audio_audproc_revb(AUDPROC_LIST list, ae_reverb_type type);//type:0~9
int swa_audio_audproc_revb_custom(AUDPROC_LIST list, ae_reverb_para1 * para);
int swa_audio_audproc_revb2(AUDPROC_LIST list, ae_reverb_para2 * para);

/*
 * Voice Cancel
 */

int swa_audio_audproc_voicecancel(AUDPROC_LIST list, int mode);

/*
 * +-------+------------------------------+------------------------------+
 * | Mode  | Left-Channel                 | Right-Channel                |
 * +-------+------------------------------+------------------------------+
 * | 0     | do nothing                   | do nothing                   |
 * | 1     | L = (L - R) / 2              | R = (L - R) / 2              |
 * | 2     | L = (L + R) / 2              | R = (L + R) / 2              |
 * | 3     | L = BPF((L + R) / 2)         | R = BPF((L + R) / 2)         |
 * | 4     | L = (L + BPF((L + R)/2) /2)  | R = (R + BPF((L + R)/2) /2)  |
 * | 5     | L = (L - BPF((L - R)/2) /2)  | R = (R - BPF((L - R)/2) /2)  |
 * | 6     | L = (L + BPF((L - R)/2) /2)  | R = (R + BPF((L - R)/2) /2)  |
 * | 7     | L = BSF(L)                   | R = BSF(R)                   |
 * | 8     | L = R                        | R = R                        |
 * | 9     | L = L                        | R = L                        |
 * +-------+------------------------------+------------------------------+
 */

/*
 * Echo
 */

typedef struct{
	int type;   // (0) regular 1 - bouncing ball 2 - reverse of 1
	int gain;   // (-6) -30 to -1 dB, 0.1 unit
	int delay;  // (300) 0 - 1000 (ms)
	int stype;  // (0)
	int shift;  // (0)
	int number; // (1)
	int mode;	// (0xff)	 	b11111111
				//switch for ch  87654321
}ae_echo_para;

int swa_audio_audproc_echo(AUDPROC_LIST list, ae_echo_para * config);

/*
 * Pitch Shift
 */

typedef struct{
    int level;  // (100) 50 ~ 100
} ae_pts_para;

int swa_audio_audproc_pts(AUDPROC_LIST list, int level);

/*
 * Bass Treble
 */
#define BTR_SET_BASS 1
#define BTR_SET_TREBLE 2

typedef struct{
	int cmd;    // 1: BTR_SET_BASS, 2:BTR_SET_TREBLE
	int fc;     // 20 ~ 96000
	int q_width;// 50 ~ 300
	int gain;   // -1200 ~ 1200
}ae_bass_treble;

int swa_audio_audproc_btr(AUDPROC_LIST list, ae_bass_treble *config);

/*
 * Low Pass, High Pass
 */
typedef struct{
	int cmd;    // 1: BTR_SET_HC, 2:BTR_SET_LC,3: BTR_SET_LP, 2:BTR_SET_HP,
	int on;     // 0: off, 1:on
	int gain;   // -600 ~ 600
	int fc;     // 20 ~ 96000
	int q;      // 50 ~ 300
}ae_btr_lhps;

int swa_audio_audproc_btr_lhps(AUDPROC_LIST list, ae_btr_lhps *config);

/*
 * Dynamic Range Compression
 */
typedef struct {
    int threshold;
    int noisefloor;
    int ratio;
    int attack;
    int release;
    int makeup;
    int usepeak;
    int logdomain;
    int kwidth;
}ae_drc_para;

int swa_audio_audproc_compressor(AUDPROC_LIST list, ae_drc_para * para);

/*
 * Noise Gate
 */
typedef struct {
    int athrd;
    int rthrd;
} ae_noise_gate;

int swa_audio_audproc_noisegate(AUDPROC_LIST list, int noise_gate[6]);

/*
 * Delay
 */
int swa_audio_audproc_delay(AUDPROC_LIST list, int delay[6]);

int swa_audio_audproc_dialenh(int list);
int swa_audio_audproc_surround(int list);
int swa_audio_audproc_resample(int list);
int swa_audio_audproc_loudctl(int list);
int swa_audio_audproc_automute(int list);
int swa_audio_audproc_vad(int list);
int swa_audio_audproc_ns(int list);
int swa_audio_audproc_agc(int list);
int swa_audio_audproc_aec(int list);
int swa_audio_audproc_afc(int list);
int swa_audio_audproc_sosf(int list);
int swa_audio_audproc_energy(AUDPROC_LIST list, unsigned int duration);
//duration 30 ~ 1000 ms
int swa_audio_audproc_get_energy(AUDPROC_LIST list, unsigned int* energy);
int swa_audio_audproc_get_peak(AUDPROC_LIST list, int* peak, int num);
int swa_audio_audproc_get_spectrum(AUDPROC_LIST list, int* sps, int num);
int swa_audio_audproc_get_mutestate(AUDPROC_LIST list, int *mute_state, int num);
int swa_audio_set_delay(int delay[6]);
/*
 * Set Delay Time for Mic in ms
 * delay should be a pointer to an array of 6 int 
 * which contain delay time in ms for each channel
 *
 * int example[6] = {0, 50, 100, 200, 100, 0};
 * swa_audio_set_delay(example);
 *
 * maximum delay for each channel is 1000ms
 */
int swa_audio_set_mute(AUDPROC_LIST list, int *mute);

#endif
