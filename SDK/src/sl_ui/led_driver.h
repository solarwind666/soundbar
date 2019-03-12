#ifndef LED_DRIVER_H
#define LED_DRIVER_H


/*
*			 a
		 _________
		|\   |   /|
	f	| h  j  k | b
		|  \ | /  |
		|   \|/   |
		|-g1---g2-|  
		|   /|\   |
	e	|  / | \  | c
		| n  m  l |
		|/	 |   \|			
		 ¯¯¯¯¯¯¯¯¯    
		     d
		     
**/

#define seg_a	(1 << 0)					
#define seg_b	(1 << 1)					
#define seg_c	(1 << 2)					
#define seg_d	(1 << 3)					
#define seg_e	(1 << 4)					
#define seg_f	 (1 << 5)					
#define seg_g1	 (1 << 6)					
#define seg_g2	 (1 << 7)					
#define seg_h	 (1 << 8)					
#define seg_j	 (1 << 9)					
#define seg_m	 (1 << 10)					
#define seg_n	 (1 << 11)					
#define seg_k	 (1 << 12)					
#define seg_l	 (1 << 13)					
#define seg_g	 (seg_g1|seg_g2)					


#define CHAR_0	 (seg_a |seg_b |seg_c |seg_d |seg_e |seg_f) 				
#define CHAR_1	 (seg_b |seg_c) 				
#define CHAR_2	 (seg_a |seg_b |seg_d |seg_e |seg_g)					
#define CHAR_3	 (seg_a |seg_b |seg_c |seg_d | seg_g)					
#define CHAR_4	 (seg_b |seg_c |seg_f | seg_g)					
#define CHAR_5	 (seg_a |seg_c |seg_d |seg_f | seg_g)					
#define CHAR_6	 (seg_a |seg_c |seg_d |seg_e |seg_f | seg_g)					
#define CHAR_7	 (seg_a |seg_b |seg_c)					
#define CHAR_8	 (seg_a |seg_b |seg_c |seg_d |seg_e |seg_f | seg_g) 				
#define CHAR_9	 (seg_a |seg_b |seg_c |seg_d |seg_f | seg_g)					
					
#define CHAR_A	 (seg_a|seg_b|seg_c|seg_e|seg_f | seg_g)					
#define CHAR_B	 (seg_a|seg_b|seg_c|seg_d|seg_j|seg_m|seg_g2)	
#define CHAR_C	 (seg_a|seg_f |seg_e|seg_d) 				
#define CHAR_D	 (seg_a|seg_b|seg_c|seg_d|seg_j|seg_m)						
#define CHAR_E	 (seg_a|seg_d|seg_e|seg_f |seg_g)					
#define CHAR_F	 (seg_a|seg_e|seg_f | seg_g)					
#define CHAR_G	 (seg_a|seg_c|seg_d|seg_e|seg_f | seg_g2)					
					
#define CHAR_H	 (seg_b|seg_c|seg_e|seg_f | seg_g)					
#define CHAR_I	 (seg_a|seg_d|seg_j|seg_m)					
#define CHAR_J	 (seg_b|seg_c|seg_d)					
#define CHAR_K	 (seg_e |seg_f | seg_g1 |seg_k|seg_l) 				
#define CHAR_L	 (seg_d |seg_e|seg_f)					
#define CHAR_M	 (seg_b|seg_c|seg_e|seg_f|seg_h|seg_k)		
#define CHAR_N	 (seg_h|seg_l |seg_b|seg_c|seg_e|seg_f)					
					
#define CHAR_O	 (seg_a|seg_b|seg_c|seg_d|seg_e|seg_f)					
#define CHAR_P	 (seg_a|seg_b|seg_e|seg_f |seg_g)					
#define CHAR_Q	 (seg_a |seg_b |seg_c|seg_d|seg_e |seg_f | seg_l)					
#define CHAR_R	 (seg_a|seg_b|seg_e|seg_f|seg_g2|seg_l)					
#define CHAR_S	 (seg_a|seg_c|seg_d|seg_f | seg_g)					
#define CHAR_T	 (seg_a|seg_j|seg_m) 			
#define CHAR_U	 (seg_b|seg_c|seg_d|seg_e|seg_f)					
#define CHAR_V	 (seg_k|seg_n|seg_e|seg_f)					
#define CHAR_W	 (seg_b|seg_c|seg_l|seg_n|seg_e|seg_f)				
#define CHAR_X	 (seg_h|seg_k|seg_l|seg_n)					
#define CHAR_Y	 (seg_h|seg_k|seg_m)					
#define CHAR_Z	 (seg_a|seg_k|seg_n|seg_d)		

#define CHAR_SPEC 	seg_g
#define CHAR_UNDERLINE 	seg_d



extern unsigned short dig_tab[5];

extern int ir_repeat_code_times;  
extern int ir_repeat_flag; 	   
extern int ir_repeat_wdtimer_start;



void led_initial(void);
void led_set_onoff(unsigned char flag);
void led_send_cmd(unsigned char cmd);
void led_send_buf(unsigned char *pbuf, unsigned char len);

void clear_seg_grid(void);

void led_timer_stop(void);




#endif


