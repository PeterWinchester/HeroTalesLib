/* witch.h
   Created - 2025/2/6
*/

#ifndef WITCH_H
#define WITCH_H

#include "htframe.h"
#include "htplayer.h"
#include "cards/tyrant.h"
#include "cards/minister.h"

/* Lv.3 女巫[攻击]
   指定一名对手，向他宣言一张牌的名称，若他的手牌或场上拥有该牌，必须将一张交付到你的手牌。
*/
bool Witch(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_witch(int          arg_player,
								 HTBasicData& arg_global_data,
								 HTBasicFunc& arg_basic_func);

#endif // WITCH_H
