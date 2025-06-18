/* master.h
   Created - 2025/2/6
*/

#ifndef MASTER_H
#define MASTER_H

#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/mimic.h"
#include "cards/minister.h"

/* Lv.2 法师[攻击]
   向一名有手牌的对手宣言 1/2/3/4 中的一个数，他必须放置此等级的牌到其场上，否则你 +1 金币。
*/
bool Master(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	);

int calc_using_pref_master(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // MASTER_H
