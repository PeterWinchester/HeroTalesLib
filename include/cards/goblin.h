/* goblin.h
   Created - 2025/2/6
*/

#ifndef GOBLIN_H
#define GOBLIN_H

#include "htframe.h"
#include "htplayer.h"
#include "cards/tyrant.h"
#include "cards/minister.h"

/* Lv.4 哥布林[攻击]
   指定一名金币比你多的对手，向你支付 1 金币。
*/
bool Goblin(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_goblin(int          arg_player,
                           HTBasicData& arg_global_data,
                           HTBasicFunc& arg_basic_func);

#endif // GOBLIN_H
