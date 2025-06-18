/* monk.h
   Created - 2025/2/6
*/

#ifndef MONK_H
#define MONK_H

#include "htplayer.h"
#include "htcards_basic.h"
#include "htgame.h"
#include "cards/bomb.h"

/* Lv.1 僧侣
   从弃牌区选 1 张 Lv.1 以外的黄色卡牌不消耗行动点打出，或将其加入手牌。
*/
bool Monk(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	);

int calc_using_pref_monk(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

#endif // MONK_H
