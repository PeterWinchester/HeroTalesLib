/* fighter.h
   Created - 2025/2/6
*/

#ifndef FIGHTER_H
#define FIGHTER_H

#include "htplayer.h"
#include "htcards_basic.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/dancer.h"
#include "cards/mimic.h"

/* Lv.0 �񶷼�
   �����ȫ�����Ʒ����ڳ��ϣ�����˷��õ����� Lv ֮��Ϊż���Ҳ��������£��� +1 ��ҡ�
*/
bool Fighter(
	int          arg_player,      // ���Ƶ�ʹ����
	int          arg_card,        // ���Ʊ�ţ������С����ϻ��������еı�ţ�
	int          arg_status,      // ����״̬�������С����ϻ���������
	int          arg_mode,        // ����ʹ��ģʽ������������Ǳ�ɮ�»���������
	HTBasicData& arg_global_data, // ȫ�����ݣ�������Ϸ״̬
	HTBasicFunc& arg_basic_func   // ������������
	);

int calc_using_pref_fighter(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // FIGHTER_H
