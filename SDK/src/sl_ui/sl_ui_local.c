/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <dirent.h>
#include <filelist.h>
#include <nxplayer.h>
#include <player_cmd.h>
#include "sl_ui_def.h"
#include "sl_ui_cmd.h"
#include "sl_ui_struct.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/
//static char *audiotype2str[AUDIO_MAX] = {"unknown", "mp3", "alac", "aac", "wma", "flac", "ape", "ac3", "dts", "wav", "ogg", "spdac3", "spddts", "pcm"};
//static char *media2str[MEDIA_MAX] = {"unknown", "sd", "usb", "bluetooth", "airplay", "dlna", "radio"};

/*???t??¡ì?????3?¡ì?id*/
static pthread_t file_load_pid = -1;

bool seek_mute_play = false;
/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
/*?¡ìaa2?*/
extern void send_cmd_2_ui(ui_cmd_t *ui_cmd);
/*??¡ì22?*/
static int file_load_thread(pthread_addr_t arg);
static int get_local_info(char *local_name, int *total_num, int *folder_num);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: get_file_total
 *
 * Description:
 *    ???¡ì?¡ì?2?¨º?¨¨??¨¨??¡ì?¨¦D?¡§¡è?¡ìa|¡§???¡§¡é?¡ì1???t?¡ìoy
 * 
 * Parameters:
 *
 * Returned Value:
 * 	  ?¡§¡é?¡ì1|¡§?????t?¡ìoy
 * 
 * Assumptions:
 *
 ****************************************************************************/
int get_file_total(void)
{
	return play_list_get_file_total();
}

/****************************************************************************
 * Name: file_load_thread
 *
 * Description:
 *    ???t??¡ì?????3?¡ì??¡ì?¡ì???¡ì2
 * 
 * Parameters:
 *    arg ?¡ì??a??¡ì???|¡§?????t|¡§?????¨¨??
 *
 * Returned Value:
 * 	  0-3?¡ì|?a?¡§o???¨¨?0-?¡ìo?¡§????¡ì1
 * 
 * Assumptions:
 *
 ****************************************************************************/
int file_load_thread(pthread_addr_t arg)
{
	int ret;
	int total_num, folder_num;
	char *search_name = (char *) arg;

	//???¡ì?¡ì?????????¨¨??|¡§???¡§¡é?¡ì1???t?¡ìoyo?¡ìa?¡§¡é?¡ì1???t?D?¡ìoy
	if (get_local_info(search_name, &total_num, &folder_num) < 0) 
	{	//??????¡ìo?¡§????¡ì1
		printf("%s %d not find music:%s\n", __func__, __LINE__, search_name); 

		ret = -SL_UI_ERROR_REGISTER;
	}
	else
	{	//?????3?¡ì|1|
		//#ifdef SL_UI_DBG
		printf("%s %d, total_num:%d, folder_num:%d\n", __func__, __LINE__, total_num, folder_num);
		//#endif

		//??¡ì??UI2???¨¨?¡§|??¡ìa????¡§|
		ui_cmd_t cmd;
		cmd.cmd = UI_CMD_FILES_IS_LOAD;
		cmd.arg2 = total_num;
		cmd.mode = folder_num;
		send_cmd_2_ui(&cmd);

		ret = SL_UI_ERROR_NULL;
	}

	file_load_pid = -1;
	return ret;
}

/****************************************************************************
 * Name: get_local_info
 *
 * Description:
 *    ??????????¨¬???¨¨??|¡§???¡§¡é?¡ì1???t?¡ìoyo?¡ìa???t?D?¡ìoy
 * 
 * Parameters:
 *    local_name ?????|¡§?????¨¨??
 *    total_num	??¨¨|¡§???|¡§???¡§¡é?¡ì1???t?D?¡ìoy??
 *    folder_num ??¨¨|¡§????¡ì?D???t|¡§?????t?D?¡ìoy??
 *
 * Returned Value:
 * 	  0-3?¡ì|1|?¡§o?-6-???¡ì?D???t?D?¡§o?-5-???¡ì?D???t
 * 
 * Assumptions:
 *
 ****************************************************************************/
static int get_local_info(char *local_name, int *total_num, int *folder_num)
{
	int i, j;
	dir_elmt_t *dir_elm;
	int file_num; 
	//3??¡ìo???¡ê¡è2?¨º?¨¨??¨¨??¡ì?¨¦D?¡§¡è?¡ìa
	playlist_init();
	//????¡ì????¡ì???¡ì?D?¡ì????|¡§????t
	file_music_enumate(local_name, 0);
	//???????¨¬???t?¡ì?¨¦D?¡§¡è?¡ìa
	fs_list_create_liner_list_for_fat();
	//???¡ì?¡ì????t?D?¡§¡é?¡ì1?¡ìoy
	*total_num = play_list_get_dir_total();
	if (*total_num <= 0) 
	{	//???¡ì?D???t?D
		printf("no local folders %s!\n", local_name);
		return -SL_UI_ERROR_NO_FOLDER;
	}
	//???¡ì?¡ì????t?¡§¡é?¡ì1?¡ìoy
	for (i=0, j=0; i<(*total_num); ++i) {
		dir_elm = play_list_get_direlm_byindex(i);
		file_num = dir_elm->file_num;
		if (0 != file_num)
		{
			j++;
		}
	}
	*folder_num = j;

	if (0 == (*folder_num)) 
	{	//???¡ì?D?¡ì?¡ì?o??¡ì????|¡§????t
		printf("%s %d this part has null music!\n", __func__, __LINE__);
		return -SL_UI_ERROR_NO_FILE;
	}

	return SL_UI_ERROR_NULL;
}

/****************************************************************************
 * Name: handle_local
 *
 * Description:
 *    ?¡§¡è?|¡§??2?¨º?¨¨??¨¨???|?¡ì?¨¨?¡ìa?¡§o?????¡ê¡è??3?¡ì???¡ì??????t?¡ì?¨¦D?¡§¡è?¡ìa
 * 
 * Parameters:
 *    local_media ?????|¡§???¡§¡è?|¡§?????¡ì?????¨¨??
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void handle_local(const char* local_media)
{
	DIR *local_dir = NULL;

	//2a?¡ìo?USB?¡ì|?¡ì?¡ì?¡§¡è????t?D?¡ìo???¨¨???¡ì11????¡ì???a
	local_dir = opendir(local_media);
	if (NULL == local_dir) 
	{	//USB?¡ì|?¡ì?¡ì?¡§¡è????t?D???¡ì???a?¡ìo?¡§????¡ì1
		printf("%s:open dir failed \n", __func__, __LINE__);
	}
	else
	{	//USB?¡ì|?¡ì?¡ì?¡§¡è????t?D???¡ì???a3?¡ì|1|
		//1??¡§¡è????t?D
		closedir(local_dir);

		if (file_load_pid > 0) 
		{	//usb???t????¡ì????¡ì?????3?¡ì??????¡ì2
			//?¡ìa?¡§o?1usb???t????¡ì????¡ì?????3?¡ì?
			pthread_cancel(file_load_pid);
			file_load_pid = -1;
		}

		if(pthread_create(&file_load_pid, NULL, (pthread_startroutine_t) file_load_thread, local_media) < 0)
		{	//???????¨¬USB???t??¡ì?????3?¡ì??¡ìo?¡§????¡ì1
			printf("%s:create thread to get usb file info fail\n", __func__);
		}
		else
		{
			if (pthread_detach(file_load_pid) < 0)
			{
				printf("%s:detach thread fail\n", __func__);
			}
			else
			{
				printf("%s:detach thread success\n", __func__);
			}
		}		
	}
}

/****************************************************************************
 * Name: handle_local_music_play
 *
 * Description:
 *    ????¡ê¡è2?¨º?¨¨??¨¨?
 * 
 * Parameters:
 *    file_index ?¡ì??a2?¨º?¨¨??¨¨?|¡§?????tD?¡ì??o?
 *    playtime 2?¨º?¨¨??¨¨?????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void handle_local_music_play(int file_index, int playtime)
{
	//???¡ì?¡ì?2?¨º?¨¨??¨¨???
	play_list_item_t item;
	if(play_list_get_file_byindex(&item, file_index) == 0)
	{	
		player_process_cmd(NP_CMD_PLAY, item.path, 0, NULL, NULL);
		usleep(100);
		if(playtime > 0)
		{	//seek|¡§???¡ì|????2?¨º?¨¨??¨¨?|¡§??????
			player_process_cmd(NP_CMD_SEEK, item.path, playtime * 1000, NULL, NULL);
			usleep(100);
		}
	}
}

/****************************************************************************
 * Name: reset_playlist
 *
 * Description:
 *    3??¡ìo???¡ê¡è2?¨º?¨¨??¨¨??¡ì?¨¦D?¡§¡è?¡ìa
 * 
 * Parameters:
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void reset_playlist(void)
{
	//3??¡ìo???¡ê¡è2?¨º?¨¨??¨¨??¡ì?¨¦D?¡§¡è?¡ìa
	playlist_init();
}

/****************************************************************************
 * Name: time2str
 *
 * Description:
 *    ?¡ì????¡ì?¨¨??¡ìo?¡§¡è???¡§¡éa?¡§¡é???¨¨????
 * 
 * Parameters:
 *    curtime |¡§??¡§¡è????¡ìo?¡§¡è??
 *    totaltime ?¡§¡é?¡ì1?¡ìo?¡§¡è??
 *    str ??¡ì??¡ìo??¡§¡éa??o?¡ì?|¡§???¡§¡é???¨¨????
 *
 * Returned Value:
 * 
 * Assumptions:
 *
 ****************************************************************************/
void time2str(int curtime, int totaltime, char *str)
{
	int cur_min, cur_sec, tot_min, tot_sec;
	cur_min = curtime/60;
	cur_sec = curtime%60;
	tot_min = totaltime/60;
	tot_sec = totaltime%60;
	sprintf(str, "%02d:%02d/%02d:%02d", cur_min, cur_sec, tot_min, tot_sec);
}



