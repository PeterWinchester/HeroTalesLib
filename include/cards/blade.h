/* blade.h
   Created - 2025/2/6
*/

#ifndef BLADE_H
#define BLADE_H

#include "htplayer.h"
#include "htgame.h"
#include "cards/fire_dragon.h"

// 检查玩家 arg_player 场上是否有魔剑
bool CheckBlade(int arg_player);

/* [魔]魔剑[持续]
   你打出“勇者”时，横置本牌，该勇者打出后放置于你的场上无需丢弃，且“勇者”的效果可指定任意一种颜色。
*/
bool Blade(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_blade(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

#endif // BLADE_H
