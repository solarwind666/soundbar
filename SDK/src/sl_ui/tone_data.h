#ifndef __TONE_DATA_H__
#define __TONE_DATA_H__

struct tone_data { 
    uint32_t off; 
    uint32_t size; 
};

extern struct tone_data datas[];
enum {
		TONE_START = -1,
    TONE_WAVE00,							/* file:tones/Long-High.wav */
		TONE_WAVE01,							/* file:tones/Long-Low.wav */
    TONE_WAVE02,							/* file:tones/Note-Falling-Scale-2.wav */
		TONE_WAVE03,							/* file:tones/Note-Falling-Scale-4.wav */
		TONE_WAVE04,							/* file:tones/Note-Rising-Scale-2.wav */
		TONE_WAVE05,							/* file:tones/Note-Rising-Scale-4.wav */
    TONE_WAVE06,							/* file:tones/mute.wav */
		TONE_WAVE07,							/* file:tones/asrstart1.wav */
		TONE_WAVE08,							/* file:tones/Disconnected-3-beep-Falling-Tone.wav */
		TONE_WAVE09,							/* file:tones/low-batt-double-beep.wav */
    TONE_WAVE10,							/* file:tones/0.wav */
		TONE_WAVE11,							/* file:tones/1.wav */
		TONE_WAVE12,							/* file:tones/2.wav */
		TONE_WAVE13,							/* file:tones/3.wav */
		TONE_WAVE14,							/* file:tones/4.wav */
		TONE_WAVE15,							/* file:tones/5.wav */
		TONE_WAVE16,							/* file:tones/6.wav */
		TONE_WAVE17,							/* file:tones/7.wav */
		TONE_WAVE18,							/* file:tones/8.wav */
		TONE_WAVE19,							/* file:tones/9.wav */
		TONE_WAVE20,							/* file:tones/Middle-0.wav */
		TONE_WAVE21,							/* file:tones/Middle-9.wav */
		TONE_WAVE22,							/* file:tones/mute-off-short-double-beep.wav */
		TONE_WAVE23,							/* file:tones/mute-on-short-double-beep.wav */
		TONE_WAVE24,							/* file:tones/phone-ring-tone.wav */
		TONE_WAVE25,							/* file:tones/ring_valkyries.wav */
		TONE_WAVE26,							/* file:tones/Short-1.wav */
    TONE_MAX,
};

#endif