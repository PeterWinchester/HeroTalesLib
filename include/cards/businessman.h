/* businessman.h
   Created - 2025/2/6
*/

#ifndef BUSINESSMAN_H
#define BUSINESSMAN_H

#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/mimic.h"
#include "cards/dancer.h"
#include "cards/minister.h"

/* Lv.1 商人[攻击]
   将你场上的一张牌加入对手的手牌，那名对手向你支付 1 金币。
*/
bool Businessman(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	);

int calc_using_pref_businessman(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // BUSINESSMAN_H
