/* monk.h
   Created - 2025/2/6
*/

#ifndef MONK_H
#define MONK_H

#include "htplayer.h"
#include "htcards_basic.h"
#include "htgame.h"
#include "cards/bomb.h"

/* Lv.1 ɮ��
   ��������ѡ 1 �� Lv.1 ����Ļ�ɫ���Ʋ������ж�����������������ơ�
*/
bool Monk(
	int          arg_player,      // ���Ƶ�ʹ����
	int          arg_card,        // ���Ʊ�ţ������С����ϻ��������еı�ţ�
	int          arg_status,      // ����״̬�������С����ϻ���������
	int          arg_mode,        // ����ʹ��ģʽ������������Ǳ�ɮ�»���������
	HTBasicData& arg_global_data, // ȫ�����ݣ�������Ϸ״̬
	HTBasicFunc& arg_basic_func   // ������������
	);

int calc_using_pref_monk(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

#endif // MONK_H
