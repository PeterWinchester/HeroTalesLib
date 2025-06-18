/* dancer.h
   Created - 2025/2/6
*/

#ifndef DANCER_H
#define DANCER_H

#include "htframe.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/mimic.h"
#include "cards/fire_dragon.h"

// 检查玩家 arg_player 以外的玩家是否有舞娘，如果有，则选择是否丢弃，并拿钱
bool CheckDancer(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

/* Lv.2 舞娘
   打出后放置在你场上。若本牌在你场上，对手获得金币后，你可以丢弃此牌，并 +1 金币。
*/
bool Dancer(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	);

int calc_using_pref_dancer(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // DANCER_H
